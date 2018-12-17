/**
 * Message transformation function definitions
 */
#include "Arduino.h"
#include "msg_transform.h"

MessageTransform::MessageTransform(PaddingInfo paddingInfo[],
                                   int paddingInfoSize,
                                   StaticAddition prefixInfo[], 
                                   int prefixInfoSize,
                                   StaticAddition suffixInfo[], 
                                   int suffixInfoSize,
                                   StaticField staticInfo[],
                                   int staticInfoSize,
                                   String messageEnd) {
  _paddingInfo = paddingInfo;
  _paddingInfoSize = paddingInfoSize;
  _prefixInfo = prefixInfo;
  _prefixInfoSize = prefixInfoSize;
  _suffixInfo = suffixInfo;
  _suffixInfoSize = suffixInfoSize;
  _staticInfo = staticInfo;
  _staticInfoSize = staticInfoSize;
  _messageEnd = messageEnd;
}

String MessageTransform::transform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return "";
  }
  String inputMessage = String(message);
  String outputMessage;
  String tmp;
  int fieldCount = 0;
  int commaPosition = inputMessage.indexOf(',');
  while(commaPosition != -1) {
    tmp = inputMessage.substring(0, commaPosition);
    // Pad fields
    for(int i = 0 ; i < _paddingInfoSize ; i++) {
      if(fieldCount == _paddingInfo[i].index) {
        tmp = leftPadNumber(tmp, _paddingInfo[i].size);
      }
    }
    // Prefix fields
    for(int i = 0 ; i < _prefixInfoSize ; i++) {
      if(fieldCount == _prefixInfo[i].index) {
        tmp = _prefixInfo[i].addition + tmp;
      }
    }
    // Suffix fields
    for(int i = 0 ; i < _suffixInfoSize ; i++) {
      if(fieldCount == _suffixInfo[i].index) {
        tmp += _suffixInfo[i].addition;
      }
    }  
    // Static fields    
    for(int i = 0 ; i < _staticInfoSize ; i++) {
      if(fieldCount == _staticInfo[i].index) {
        tmp = _staticInfo[i].value;
      }
    }
    outputMessage += tmp;
    outputMessage += ',';
    inputMessage = inputMessage.substring(commaPosition + 1);
    commaPosition = inputMessage.indexOf(',');
    fieldCount++;
  }
  outputMessage += _messageEnd;
  outputMessage += inputMessage;
  return outputMessage;
}
