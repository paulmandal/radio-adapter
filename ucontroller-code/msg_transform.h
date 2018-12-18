/**
 * MessageTransform class definition
 */
#ifndef MessageTransform_h
#define MessageTransform_h

#include "Arduino.h"
#include "string_manip.h"

char *defaultTransform(char *message, Stream &ser);
char *ggaTransform(char *message, Stream &ser);
char *gllTransform(char *message, Stream &ser);
char *rmcTransform(char *message, Stream &ser);
char *vtgTransform(char *message, Stream &ser);
char *gsaTransform(char *message, Stream &ser);
char *gsvTransform(char *message, Stream &ser);
char *zdaTransform(char *message, Stream &ser);

#endif
