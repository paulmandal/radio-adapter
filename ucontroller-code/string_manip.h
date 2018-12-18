/**
 * Header for string manipulation functions
 */
#ifndef StringManip_h
#define StringManip_h

#include "Arduino.h"

char *leftPadNumber(char *input, int targetLength);
char *rightPadNumber(char *input, int targetLength);

#endif
