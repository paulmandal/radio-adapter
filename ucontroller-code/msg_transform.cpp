/**
 * Message transformation function definitions
 */
#include <stdbool.h>

#include "Arduino.h"

#define BUFFER_SIZE 128

/**
 * Transform a variable-length Garmin NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *defaultTransform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return NULL;
  }

  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));

  // No processing, just copy the message to our output allocation
  strcpy(outputMessage, message);
  return outputMessage;
}

/**
 * Transform a variable-length Garmin GGA NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *ggaTransform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return NULL;
  }

  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));

  strtok(message, ",");
  double timestamp = atof(strtok(NULL, ","));;
  double lat = atof(strtok(NULL, ","));
  char *northSouth = strtok(NULL, ",");
  double lon = atof(strtok(NULL, ","));
  char *eastWest = strtok(NULL, ",");
  int fixQuality = atoi(strtok(NULL, ","));
  int numSatellites = atoi(strtok(NULL, ","));
  float horizontalDilutionOfPrecision = atof(strtok(NULL, ","));
  float altitude = atof(strtok(NULL, ","));
  char *altitudeUnit = strtok(NULL, ",");
  float geoIdHeight = atof(strtok(NULL, ","));
  char *geoIdHeightUnit = strtok(NULL, ",");
  long timeSinceLastUpdate = atol(strtok(NULL, ","));
  long stationId = atol(strtok(NULL, "*"));

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
char *gllTransform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return NULL;
  }

  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));

  strtok(message, ",");
  double lat = atof(strtok(NULL, ","));
  char *northSouth = strtok(NULL, ",");
  double lon = atof(strtok(NULL, ","));
  char *eastWest = strtok(NULL, ",");
  double timestamp = atof(strtok(NULL, ","));
  char *statusStr = strtok(NULL, ",");
  char *unknown = strtok(NULL, "*");

  sprintf(outputMessage, "$GPGLL,%09.4f,%s,%09.4f,%s,%010.3f,%s,%s*FF",
                         lat,
                         northSouth,
                         lon,
                         eastWest,
                         timestamp,
                         statusStr,
                         unknown);

  return outputMessage;
}

/**
 * Transform a variable-length Garmin RMC NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *rmcTransform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return NULL;
  }

  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));

  strtok(message, ",");
  double timestamp = atof(strtok(NULL, ","));
  char *statusStr = strtok(NULL, ",");
  double lat = atof(strtok(NULL, ","));
  char *northSouth = strtok(NULL, ",");
  double lon = atof(strtok(NULL, ","));
  char *eastWest = strtok(NULL, ",");
  float currentSpeed = atof(strtok(NULL, ","));
  float trackDegrees = atof(strtok(NULL, ","));
  long utDate = atol(strtok(NULL, ","));
  float variation = atof(strtok(NULL, ","));
  char *trackEastWest = strtok(NULL, ",");

  sprintf(outputMessage, "$GPRMC,%010.3f,%s,%09.4f,%s,%010.4f,%s,%07.2f,%06.2f,%06ld,,*FF",
                         timestamp,
                         statusStr,
                         lat,
                         northSouth,
                         lon,
                         eastWest,
                         currentSpeed,
                         trackDegrees,
                         utDate);

  return outputMessage;
}

/**
 * Transform a variable-length Garmin VTG NMEA message into a fixed-length
 * Yaesu VX-8DR NMEA message
 */
char *vtgTransform(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return NULL;
  }

  char *outputMessage = (char *)calloc(BUFFER_SIZE, sizeof(char));

  strtok(message, ",");
  double degreesTrue = atof(strtok(NULL, ","));
  char *degreesTrueRelative = strtok(NULL, ",");
  double degreesMagnetic = atof(strtok(NULL, ","));
  char *degreesMagneticRelative = strtok(NULL, ",");
  double currentSpeed = atof(strtok(NULL, ","));
  char *speedUnit = strtok(NULL, ",");
  double speedOverGround = atof(strtok(NULL, ","));
  char *speedOverGroundUnit = strtok(NULL, ",");
  char *unknown = strtok(NULL, "*");

  sprintf(outputMessage, "$GPVTG,,%s,,%s,%4.2f,%s,%3.1f,%s,%s*FF",
                         degreesTrueRelative,
                         degreesMagneticRelative,
                         currentSpeed,
                         speedUnit,
                         speedOverGround,
                         speedOverGroundUnit,
                         unknown);

  return outputMessage;
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
