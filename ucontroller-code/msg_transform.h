/**
 * MessageTransform class definition
 */
#ifndef MessageTransform_h
#define MessageTransform_h

#include "Arduino.h"
#include "string_manip.h"

struct FieldResize {
  int index;
  int size;
};

struct FieldAddition {
  int index;
  const char *addition;
};

struct ConstantField {
  int index;
  const char *value;
};

class MessageTransform {
  public:
    MessageTransform(FieldResize leftPaddings[],
                     int leftPaddingsSize,
                     FieldResize rightPaddings[],
                     int rightPaddingsSize,
                     FieldResize rightShrinks[],
                     int rightShrinksSize,
                     FieldAddition prefixes[],
                     int prefixesSize,
                     FieldAddition suffixes[],
                     int suffixesSize,
                     ConstantField constants[],
                     int constantsSize,
                     int drops[],
                     int dropsSize,
                     const char *messageEnd);
    char *transform(char *message);
  private:
    FieldResize *_leftPaddings;
    int _leftPaddingsSize;
    FieldResize *_rightPaddings;
    int _rightPaddingsSize;
    FieldResize *_rightShrinks;
    int _rightShrinksSize;
    FieldAddition *_prefixes;
    int _prefixesSize;
    FieldAddition *_suffixes;
    int _suffixesSize;
    ConstantField *_constants;
    int _constantsSize;
    int *_drops;
    int _dropsSize;
    const char *_messageEnd;
};

#endif
