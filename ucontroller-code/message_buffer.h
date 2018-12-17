/**
 * Message buffer for serial input
 */
#ifndef MessageBuffer_h
#define MessageBuffer_h

#include "Arduino.h"

class MessageBuffer {
  public:
    MessageBuffer(int bufferSize);
    void write(char c);
    void copyTo(MessageBuffer dest);
    char *getMessage();
    void clear();
  private:
    int _bufferPosition;
    int _bufferSize;
    char *_msgBuffer;
};

#endif
