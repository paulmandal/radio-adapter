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
                     FieldResize rightShrinks[],
                     int rightShrinksSize,
                     FieldAddition prefixes[],
                     int prefixesSize,
                     FieldAddition suffixes[],
                     int suffixesSize,
                     ConstantField constants[],
                     int constantsSize,
                     const char *messageEnd);
    char *transform(char *message);
  private:
    FieldResize *_leftPaddings;
    int _leftPaddingsSize;
    FieldResize *_rightShrinks;
    int _rightShrinksSize;
    FieldAddition *_prefixes;
    int _prefixesSize;
    FieldAddition *_suffixes;
    int _suffixesSize;
    ConstantField *_constants;
    int _constantsSize;
    const char *_messageEnd;
};

#endif
