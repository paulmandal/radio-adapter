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

extern MessageTransform ggaTransform;

NeoSWSerial radioSerial(9, 8);
NeoSWSerial debugSerial(7, 6);

void setup() {
  NeoSerial.attachInterrupt(handleGpsInput);
  NeoSerial.begin(4800);
  radioSerial.begin(9600);
  debugSerial.attachInterrupt(handleDebugInput);
  debugSerial.begin(9600);
  debugSerial.println("Debug Serial Output - Application started.");
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
  // Determine the message type
  String outputMsg;
  boolean sendMsgToRadio = false;
  if(strncmp(message, "$GPGGA", 6) == 0) {
    //outputMsg = translateGga(message);
    outputMsg = ggaTransform.transform(message);
    sendMsgToRadio = true;
  } else if(strncmp(message, "$GPGLL", 6) == 0) {
    outputMsg = translateGgl(message);
    //sendMsgToRadio = true;
  } else if(strncmp(message, "$GPRMC", 6) == 0) {
    outputMsg = translateRmc(message);
    //sendMsgToRadio = true;
  } else if(strncmp(message, "$GPVTG", 6) == 0) {
    outputMsg = translateVtg(message);
    //sendMsgToRadio = true;
  } else if(strncmp(message, "$XFER", 5) == 0) {
    // handle cmd
    xferMessages = !xferMessages;
    debugSerial.print("xferMessages: ");
    debugSerial.println(xferMessages); 
  }
  if(sendMsgToRadio && xferMessages) {
    sendToRadio(outputMsg);
  }
}

String translateGga(char *message) {
  // Check if we have a fix before attempting to translate msg
  if(message[7] == ',') {
    return;
  }
  String gpsMsg = String(message);  
  String outputMsg;
  String tmp;
  int paddingIndexes[] = {7, 8, 9, 11, 14};
  int paddingSizes[] = {2, 4, 7, 6, 4};
  int count = 0;
  int comma = gpsMsg.indexOf(',');
  while(comma != -1) {
    tmp = gpsMsg.substring(0, comma);
    for(int i = 0 ; i < (sizeof(paddingIndexes)/sizeof(int)) ; i++) {
      if(count == paddingIndexes[i]) {
        tmp = leftPadNumber(tmp, paddingSizes[i]);
      }
    }
    if(count == 1) {
      tmp += ".000";
    } else if(count == 13) {
      tmp = "000.0";
    }
    outputMsg += tmp;
    outputMsg += ",";
    gpsMsg = gpsMsg.substring(comma + 1);
    comma = gpsMsg.indexOf(',');
    count++;
  }
  outputMsg += "0000";
  outputMsg += gpsMsg;
  return outputMsg;
}

String translateGgl(char *message) {
    // Does nothing -- need to figure out message syntax
    String outputMsg = "";
    return outputMsg;
}

String translateRmc(char *message) {
  String gpsMsg = String(message);
  String outputMsg = gpsMsg.substring(0, 13);
  return outputMsg;
//  Serial.println(outputMsg);  
}

String translateVtg(char *message) {
    // Does nothing
    String outputMsg = "";
    return outputMsg;
}

/**
 * Send a message to the radio and debug serial ports
 */
void sendToRadio(String outputMsg) {
  radioSerial.listen();
  radioSerial.print(outputMsg);
  debugSerial.listen();
  debugSerial.print("uC->radio: ");
  debugSerial.print(outputMsg);
}

