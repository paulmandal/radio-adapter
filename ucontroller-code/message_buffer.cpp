/**
 * Message buffer function definitions
 */
#include "Arduino.h"
#include "message_buffer.h"

/**
 * Initialize a MessageBuffer, allocates memory for the buffer
 */
MessageBuffer::MessageBuffer(int bufferSize) {
  _bufferPosition = 0;
  _bufferSize = bufferSize;
  _msgBuffer = (char*)calloc(bufferSize, sizeof(char));
}

/**
 * Write a character to this MessageBuffer
 */
void MessageBuffer::write(char c) {
  _msgBuffer[_bufferPosition] = c;
  _bufferPosition++;
  if (_bufferPosition >= _bufferSize) {
    _bufferPosition = 0;
  }
}

/**
 * Copy the contents of this MessageBuffer to another MessageBuffer
 */
void MessageBuffer::copyTo(MessageBuffer dest) {
  dest.clear();
  for(int i = 0 ; i < _bufferPosition ; i++) {
    dest.write(_msgBuffer[i]);
  }
}

char *MessageBuffer::getMessage() {
  return _msgBuffer;
}

/**
 * Clear the message buffer by setting the first character to the termination
 * character and resetting the buffer position to 0
 */
void MessageBuffer::clear() {
  for(int i = 0 ; i < _bufferSize ; i++) {
    _msgBuffer[i] = '\0';
  }
  _bufferPosition = 0;
}
