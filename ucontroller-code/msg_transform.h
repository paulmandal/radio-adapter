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
                     StaticAddition prefixInfo[], 
                     StaticAddition suffixInfo[], 
                     StaticField staticInfo[],
                     String messageEnd);
    String transform(char *message);
  private:
    PaddingInfo *_paddingInfo;
    StaticAddition *_prefixInfo;
    StaticAddition *_suffixInfo;
    StaticField *_staticInfo;
    String _messageEnd;
};

#endif
