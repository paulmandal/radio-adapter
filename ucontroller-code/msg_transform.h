/**
 * MessageTransform class definition
 */
#ifndef MessageTransform_h
#define MessageTransform_h

#include "Arduino.h"
#include "string_manip.h"

struct FieldPadding {
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
    MessageTransform(FieldPadding leftPaddings[],
                     int leftPaddingsSize,
                     FieldAddition prefixes[],
                     int prefixesSize,
                     FieldAddition suffixes[],
                     int suffixesSize,
                     ConstantField constants[],
                     int constantsSize,
                     const char *messageEnd);
    char *transform(char *message);
  private:
    FieldPadding *_leftPaddings;
    int _leftPaddingsSize;
    FieldAddition *_prefixes;
    int _prefixesSize;
    FieldAddition *_suffixes;
    int _suffixesSize;
    ConstantField *_constants;
    int _constantsSize;
    const char *_messageEnd;
};

#endif
