/**
 * Message transformation configuration definitions
 */
 
#ifndef MessageTransformMapping_h
#define MessageTransformMapping_h

#include "msg_transform.h"

struct TransformMapping {
  const char *nmeaMessageType;
  char *(*transform)(char *, Stream &ser);
};

extern const TransformMapping transformMap[] = {
  {"$GPGGA", ggaTransform},
  {"$GPGLL", gllTransform},
  {"$GPRMC", rmcTransform},
  {"$GPVTG", vtgTransform},
  {"$GPGSA", gsaTransform},
  {"$GPGSV", gsvTransform},
  {"$GPZDA", zdaTransform}
};

#endif
