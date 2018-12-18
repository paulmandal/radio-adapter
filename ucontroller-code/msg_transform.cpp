/**
 * Message transformation function definitions
 */
#include <stdbool.h>

#include "Arduino.h"
#include "msg_transform.h"

#define BUFFER_SIZE 128

/**
 * Transform a variable-length Garmin NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *defaultTransform(char *message, Stream &ser) {
  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));
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
char *ggaTransform(char *message, Stream &ser) {
  ser.println("ggaTransform");
  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return outputMessage;
  }

  char *p;
  double timestamp;
  double lat;
  char *northSouth;
  double lon;
  char *eastWest;
  int fixQuality;
  int numSatellites;
  float horizontalDilutionOfPrecision;
  float altitude;
  char *altitudeUnit;
  float geoIdHeight;
  char *geoIdHeightUnit;
  long timeSinceLastUpdate;
  long stationId;

  p = strtok(message, ",");
  p = strtok(NULL, ",");
  timestamp = atof(p);
  p = strtok(NULL, ",");
  lat = atof(p);
  p = strtok(NULL, ",");
  northSouth = p;
  p = strtok(NULL, ",");
  lon = atof(p);
  p = strtok(NULL, ",");
  eastWest = p;
  p = strtok(NULL, ",");
  fixQuality = atoi(p);
  p = strtok(NULL, ",");
  numSatellites = atoi(p);
  p = strtok(NULL, ",");
  horizontalDilutionOfPrecision = atof(p);
  p = strtok(NULL, ",");
  altitude = atof(p);
  p = strtok(NULL, ",");
  altitudeUnit = p;
  p = strtok(NULL, ",");
  geoIdHeight = atof(p);
  p = strtok(NULL, ",");
  geoIdHeightUnit = p;
  p = strtok(NULL, ",");
  timeSinceLastUpdate = atol(p);
  p = strtok(NULL, ",");
  stationId = atol(p);

  sprintf(outputMessage, "$GPGGA,%010.3f,%09.4f,%s,%010.4f,%s,%1d,%02d,%04.1f,%07.1f,%s,%06.1f,%s,%05.1f,%04d*FF",
                         timestamp,
                         lat,
                         northSouth,
                         lon,
                         eastWest,
                         fixQuality,
                         numSatellites,
                         horizontalDilutionOfPrecision,
                         altitude,
                         altitudeUnit,
                         geoIdHeight,
                         geoIdHeightUnit,
                         timeSinceLastUpdate,
                         stationId);
  return outputMessage;
}

/**
 * Transform a variable-length Garmin GLL NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gllTransform(char *message, Stream &ser) {
  ser.println("gllTransform");
  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return outputMessage;
  }

  ser.println("message has contents");
  char *p;
  double lat;
  char *northSouth;
  double lon;
  char *eastWest;
  double timestamp;
  char *status;

  p = strtok(message, ",");
  p = strtok(NULL, ",");
  lat = atof(p);
  p = strtok(NULL, ",");
  northSouth = p;
  p = strtok(NULL, ",");
  lon = atof(p);
  p = strtok(NULL, ",");
  eastWest = p;
  p = strtok(NULL, ",");
  timestamp = atof(p);
  p = strtok(NULL, ",");
  status = p;

  ser.println("read all tokens");
  sprintf(outputMessage, "$GPGLL,%09.4f,%s,%09.4f,%s,%010.3f,%s,%s*FF",
                         lat,
                         northSouth,
                         lon,
                         eastWest,
                         timestamp,
                         status);

  ser.print("output message: ");
  ser.println(outputMessage);
  return outputMessage;
}

/**
 * Transform a variable-length Garmin RMC NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *rmcTransform(char *message, Stream &ser) {
  return defaultTransform(message, ser);
}

/**
 * Transform a variable-length Garmin VTG NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *vtgTransform(char *message, Stream &ser) {
  return defaultTransform(message, ser);
}

/**
 * Transform a variable-length Garmin GSA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gsaTransform(char *message, Stream &ser) {
  return defaultTransform(message, ser);
}

/**
 * Transform a variable-length Garmin GSV NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *gsvTransform(char *message, Stream &ser) {
  return defaultTransform(message, ser);
}

/**
 * Transform a variable-length Garmin ZDA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *zdaTransform(char *message, Stream &ser) {
  return defaultTransform(message, ser);
}
