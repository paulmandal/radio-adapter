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
    void copyTo(volatile MessageBuffer &dest);
    char *getMessage();
    void clear();
    int length();
  private:
    int _bufferPosition;
    int _bufferSize;
    char *_msgBuffer;
};

#endif
