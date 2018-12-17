//Garmin and Yaesu support:
//
//GGA
//GGL
//RMC
//VTG
//
//
//Yaesu supports but not Garmin:
//
//GSA
//GSV
//ZDA
//


#include <SoftwareSerial.h>


const int MSG_BUFFER_SIZE = 256;

char *msgBuffer;
char bufferPos = 0;

char *debugMsgBuffer;
char debugBufferPos = 0;

char readByte;
boolean xferMessages = true;

SoftwareSerial radioSerial(9, 8);
SoftwareSerial debugSerial(7, 6);

void setup() {
  Serial.begin(4800);
  radioSerial.begin(9600);  
  debugSerial.begin(9600);
  debugSerial.println("Debug Serial Output - Application started.");
  msgBuffer = (char*)calloc(MSG_BUFFER_SIZE, sizeof(char));
  debugMsgBuffer = (char*)calloc(MSG_BUFFER_SIZE, sizeof(char));
}


void loop() {
  while(Serial.available() > 0) {
    readByte = Serial.read();    
    if(readByte == '$') {
      // New message is beginning
      bufferPos = 0;
    }    
    msgBuffer[bufferPos] = readByte;
    bufferPos++;
    if(readByte == '\n') {
      // Message is finished, process
      handleMessage(msgBuffer);
      bufferPos = 0;
    } else if(bufferPos >= MSG_BUFFER_SIZE) {
      bufferPos = 0;
    }
  }
  while(debugSerial.available() > 0) {    
    readByte = debugSerial.read();
    if(readByte == '$') {
      debugBufferPos = 0;
    }
    debugMsgBuffer[debugBufferPos] = readByte;
    debugBufferPos++;
    if(readByte == '\n') {
      handleMessage(debugMsgBuffer);
      debugBufferPos = 0;
    } else if(debugBufferPos >= MSG_BUFFER_SIZE) {
      debugBufferPos = 0;
    }
  }
}

void handleMessage(char *message) {
  debugSerial.print("GPS->uC: ");
  debugSerial.write(message, bufferPos);
  // Determine the message type
  String outputMsg;
  boolean sendMsgToRadio = false;
  if(strncmp(message, "$GPGGA", 6) == 0) {
    outputMsg = translateGga(message);
    sendMsgToRadio = true;
  } else if(strncmp(message, "$GPGGL", 6) == 0) {
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
        tmp = padNumber(tmp, paddingSizes[i]);
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

void sendToRadio(String outputMsg) {
  radioSerial.print(outputMsg);
  debugSerial.print("uC->RADIO: ");
  debugSerial.print(outputMsg);
}

String padNumber(String input, int count) {  
  String tmp = "";
  boolean negative = false;
  if(input.charAt(0) == '-') {
    tmp += '-';
    negative = true;
  }
  for(int i = input.length() ; i < count ; i++) {
    tmp += '0';
  }
  if(negative) {
    tmp += input.substring(1);
  } else {
    tmp += input;
  }
  return tmp;
}

