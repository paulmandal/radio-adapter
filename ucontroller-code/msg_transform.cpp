/**
 * Message transformation function definitions
 */
#include <stdbool.h>

#include "Arduino.h"
#include "msg_transform.h"

/**
 * Transform a variable-length Garmin NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *defaultTransform(char *message) {
  char *outputMessage = (char *)calloc(256, sizeof(char)); // TODO: FIXME: replace this with something else
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return outputMessage;
  }

  // No processing, just copy the message to our output allocation
  strcpy(outputMessage, message);
  return outputMessage;
}

/**
 * Transform a variable-length Garmin GGA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *ggaTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin GLL NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gllTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin RMC NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *rmcTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin VTG NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *vtgTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin GSA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gsaTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin GSV NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gsvTransform(char *message) {
  return defaultTransform(message);
}

/**
 * Transform a variable-length Garmin ZDA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *zdaTransform(char *message) {
  return defaultTransform(message);
}
