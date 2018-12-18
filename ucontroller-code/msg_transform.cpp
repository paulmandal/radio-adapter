/**
 * Message transformation function definitions
 */
#include "Arduino.h"
#include "msg_transform.h"

MessageTransform::MessageTransform(FieldResize leftPaddings[],
                                   int leftPaddingsSize,
                                   FieldResize rightShrinks[],
                                   int rightShrinksSize,
                                   FieldAddition prefixes[],
                                   int prefixesSize,
                                   FieldAddition suffixes[],
                                   int suffixesSize,
                                   ConstantField constants[],
                                   int constantsSize,
                                   const char *messageEnd) {
  _leftPaddings = leftPaddings;
  _leftPaddingsSize = leftPaddingsSize;
  _rightShrinks = rightShrinks;
  _rightShrinksSize = rightShrinksSize;
  _prefixes = prefixes;
  _prefixesSize = prefixesSize;
  _suffixes = suffixes;
  _suffixesSize = suffixesSize;
  _constants = constants;
  _constantsSize = constantsSize;
  _messageEnd = messageEnd;
}

/**
 * Transform a variable-length Garmin NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *MessageTransform::transform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return "";
  }

  char *outputMessage = (char *)calloc(256, sizeof(char)); // TODO: FIXME: replace this with something else
  char *tmp = (char *)calloc(32, sizeof(char)); // TODO: FIXME: replace this with another value
  int fieldCount = 0;
  char *lastFieldStart = message;
  char *fieldEnd = strchr(message, ',');
  while(fieldEnd != NULL) {
    int fieldLength = fieldEnd - lastFieldStart;
    strncpy(tmp, lastFieldStart, fieldLength);
    tmp[fieldLength] = '\0';
    // Pad left fields
    for(int i = 0 ; i < _leftPaddingsSize ; i++) {
      if(fieldCount == _leftPaddings[i].index) {
        char *padded = leftPadNumber(tmp, _leftPaddings[i].size);
        strcpy(tmp, padded);
        free(padded);
      }
    }
    // Prefix fields
    for(int i = 0 ; i < _prefixesSize ; i++) {
      if(fieldCount == _prefixes[i].index) {
        char *swapStr = (char *)calloc(strlen(tmp) + 1, sizeof(char));
        strcpy(swapStr, tmp);
        strcpy(tmp, _prefixes[i].addition);
        strcat(tmp, swapStr);
        free(swapStr);
      }
    }
    // Suffix fields
    for(int i = 0 ; i < _suffixesSize ; i++) {
      if(fieldCount == _suffixes[i].index) {
        strcat(tmp, _suffixes[i].addition);
      }
    }  
    // Static fields    
    for(int i = 0 ; i < _constantsSize ; i++) {
      if(fieldCount == _constants[i].index) {
        strcpy(tmp, _constants[i].value);
      }
    }
    // Shrink fields
    for(int i = 0 ; i < _rightShrinksSize ; i++) {
      if(fieldCount == _rightShrinks[i].index) {
        if(strlen(tmp) > _rightShrinks[i].size) {
          tmp[_rightShrinks[i].size] = '\0';
        }
      }
    }
    // Drop fields
    strcat(outputMessage, tmp);
    strcat(outputMessage, ",");
    lastFieldStart = fieldEnd + 1;
    fieldEnd = strchr(lastFieldStart, ',');
    fieldCount++;
  }
  strcat(outputMessage, _messageEnd);
  strcat(outputMessage, lastFieldStart);
  free(tmp);
  return outputMessage;
}
