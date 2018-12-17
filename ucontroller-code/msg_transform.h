/**
 * MessageTransform class definition
 */
#ifndef MessageTransform_h
#define MessageTransform_h

#include "Arduino.h"
#include "string_manip.h"

struct PaddingInfo {
  int index;
  int size;
};

struct StaticAddition {
  int index;
  String addition;
};

struct StaticField {
  int index;
  String value;
};

class MessageTransform {
  public:
    MessageTransform(PaddingInfo paddingInfo[],
                     int paddingInfoSize,
                     StaticAddition prefixInfo[], 
                     int prefixInfoSize,
                     StaticAddition suffixInfo[], 
                     int suffixInfoSize,
                     StaticField staticInfo[],
                     int staticInfoSize,
                     String messageEnd);
    String transform(char *message);
  private:
    PaddingInfo *_paddingInfo;
    int _paddingInfoSize;
    StaticAddition *_prefixInfo;
    int _prefixInfoSize;
    StaticAddition *_suffixInfo;
    int _suffixInfoSize;
    StaticField *_staticInfo;
    int _staticInfoSize;
    String _messageEnd;
};

#endif
