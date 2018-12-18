/**
 * Transforms GPS NMEA messages from the variable-length format used by Garmin (and probably others) into
 * the fixed-lenght format used by the Yaesu VX-8DR
 */
// Uncomment the line below to enable debugging output to the UC-DBG port
#define DEBUG_PORT_OUTPUT_ENABLED

#include <NeoSWSerial.h>
#include <NeoHWSerial.h>

#include "message_buffer.h"
#include "string_manip.h"
#include "msg_transform.h"
#include "transform_mapping.h"

const int MSG_BUFFER_SIZE = 256;

volatile MessageBuffer gpsMessageBuffer(MSG_BUFFER_SIZE);
volatile MessageBuffer debugMessageBuffer(MSG_BUFFER_SIZE);
volatile MessageBuffer queuedMessage(MSG_BUFFER_SIZE);

boolean xferMessages = true;

extern const TransformMapping transformMap[];

NeoSWSerial radioSerial(9, 8);

#ifdef DEBUG_PORT_OUTPUT_ENABLED
NeoSWSerial debugSerial(7, 6);
#endif

void setup() {
  NeoSerial.attachInterrupt(handleGpsInput);
  NeoSerial.begin(4800);
  radioSerial.begin(9600);

#ifdef DEBUG_PORT_OUTPUT_ENABLED
  debugSerial.attachInterrupt(handleDebugInput);
  debugSerial.begin(9600);
  debugSerial.println("Debug serial output - application started.");
#endif
}

/**
 * Main loop -- check for any queued message to be processed
 * TODO: this can be improved by using the microcontroller's sleep functionality and Neo*Serial's interrupt-driven input handling
 */
void loop() {
  if(queuedMessage.length() > 0) {
    handleMessage(queuedMessage.getMessage());
    queuedMessage.clear();
  }
}

/**
 * Handle input interrupt on the GPS port
 */
void handleGpsInput(char c) {
  handleSerialInput(c, gpsMessageBuffer);
}

/**
 * Handle input interrupt on the debug port
 */
void handleDebugInput(char c) {
  handleSerialInput(c, debugMessageBuffer);
}

/**
 * Handle input interrupt -- write the input to a MessageBuffer, check for start/end of message
 * If we hit the end of the message queue the message up for handling
 */
void handleSerialInput(char c, volatile MessageBuffer &messageBuffer) {
    if(c == '$') {
      // New message is beginning
      messageBuffer.clear();
    }
    messageBuffer.write(c);
    if(c == '\n') {
      // Message is finished, queue for processing
      messageBuffer.copyTo(queuedMessage);
      messageBuffer.clear();
    }  
}

/**
 * Handle a completed message -- determine the message type and apply the appropriate transformation
 */
void handleMessage(char *message) {
#ifdef DEBUG_PORT_OUTPUT_ENABLED
  debugSerial.print("GPS->uC:   ");
  debugSerial.print(message);
#endif

  // Check for debugging messages
  if(strncmp(message, "$XFER", 5) == 0) {
    // handle debug message transfer toggle command
    xferMessages = !xferMessages;

#ifdef DEBUG_PORT_OUTPUT_ENABLED
    debugSerial.print("xferMessages: ");
    debugSerial.println(xferMessages);
#endif
  }

  if(!xferMessages) {
    // No need to process messages if we're not sending them to the radio
    return;
  }

  // Determine the message type and apply the appropriate transform
  char *outputMessage;
  for(int i = 0 ; i < (sizeof(transformMap) / sizeof(TransformMapping)) ; i++) {
    if(strncmp(message, transformMap[i].nmeaMessageType, 6) == 0) {
      outputMessage = transformMap[i].transform(message);
      break;
    }
  }

  if(strlen(outputMessage) > 0 && xferMessages) {
    sendToRadio(outputMessage);
  }
  free(outputMessage);
}

/**
 * Send a message to the radio and debug serial ports
 */
void sendToRadio(char *message) {
  radioSerial.listen();
  radioSerial.print(message);

#ifdef DEBUG_PORT_OUTPUT_ENABLED
  debugSerial.listen();
  debugSerial.print("uC->radio: ");
  debugSerial.print(message);
#endif
}

