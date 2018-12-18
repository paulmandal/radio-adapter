/**
 * Transforms GPS NMEA messages from the variable-length format used by Garmin (and probably others) into
 * the fixed-lenght format used by the Yaesu VX-8DR
 */
#include <NeoSWSerial.h>
#include <NeoHWSerial.h>

#include "message_buffer.h"
#include "string_manip.h"
#include "msg_transform.h"
#include "transform_configs.h"

const int MSG_BUFFER_SIZE = 256;

volatile MessageBuffer gpsMessageBuffer(MSG_BUFFER_SIZE);
volatile MessageBuffer debugMessageBuffer(MSG_BUFFER_SIZE);
volatile MessageBuffer queuedMessage(MSG_BUFFER_SIZE);

boolean xferMessages = true;

extern const TransformMapping transformMap[];

NeoSWSerial radioSerial(9, 8);
NeoSWSerial debugSerial(7, 6);

void setup() {
  NeoSerial.attachInterrupt(handleGpsInput);
  NeoSerial.begin(4800);
  radioSerial.begin(9600);

  debugSerial.attachInterrupt(handleDebugInput);
  debugSerial.begin(9600);
  debugSerial.println("Debug serial output - application started.");
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
  debugSerial.print("GPS->uC:   ");
  debugSerial.print(message);

  // Check for debugging messages
  if(strncmp(message, "$XFER", 5) == 0) {
    // handle debug message transfer toggle command
    xferMessages = !xferMessages;
    debugSerial.print("xferMessages: ");
    debugSerial.println(xferMessages);
  }

  if(!xferMessages) {
    // No need to process messages if we're not sending them to the radio
    return;
  }

  // Determine the message type and apply the appropriate transform
  char *outputMessage;
  for(int i = 0 ; i < (sizeof(transformMap) / sizeof(TransformMapping)) ; i++) {
    if(strncmp(message, transformMap[i].nmeaMessageType, 6) == 0) {
      outputMessage = transformMap[i].transformer.transform(message);
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

  debugSerial.listen();
  debugSerial.print("uC->radio: ");
  debugSerial.print(message);
}

