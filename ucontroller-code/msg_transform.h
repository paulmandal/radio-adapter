/**
 * MessageTransform class definition
 */
#ifndef MessageTransform_h
#define MessageTransform_h

#include "Arduino.h"
#include "string_manip.h"

char *defaultTransform(char *message);
char *ggaTransform(char *message);
char *gllTransform(char *message);
char *rmcTransform(char *message);
char *vtgTransform(char *message);
char *gsaTransform(char *message);
char *gsvTransform(char *message);
char *zdaTransform(char *message);

#endif
