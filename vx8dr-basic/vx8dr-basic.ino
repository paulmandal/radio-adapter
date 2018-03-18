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

char msgBuffer[MSG_BUFFER_SIZE];
char bufferPos = 0;

char readByte;
boolean first;

SoftwareSerial radioSerial(9, 8);
SoftwareSerial debugSerial(7, 6);

void setup() {
  Serial.begin(4800);
  radioSerial.begin(9600);  
  debugSerial.begin(9600);
  debugSerial.println("Debug Serial Output - Application started.");
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
      handleMessage();
      bufferPos = 0;
    } else if(bufferPos >= MSG_BUFFER_SIZE) {
      bufferPos = 0;
    }
  }
  first = false;
}

void handleMessage() {
  debugSerial.print("GPS->uC: ");
  debugSerial.println(msgBuffer);
  // Determine the message type
  if(strncmp(msgBuffer, "$GPGGA", 6) == 0) {
    translateGga();
  } else if(strncmp(msgBuffer, "$GPGGL", 6) == 0) {
    translateGgl();
  } else if(strncmp(msgBuffer, "$GPRMC", 6) == 0) {
    translateRmc();
  } else if(strncmp(msgBuffer, "$GPVTG", 6) == 0) {
    translateVtg();
  }
}

void translateGga() {
  // Check if we have a fix before attempting to translate msg
  if(msgBuffer[7] == ',') {
    return;
  }
  String gpsMsg = String(msgBuffer);  
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
  sendToRadio(outputMsg);
}

void translateGgl() {
    // Does nothing -- need to figure out message syntax
}

void translateRmc() {
  String gpsMsg = String(msgBuffer);
  String outputMsg = gpsMsg.substring(0, 13);
//  Serial.println(outputMsg);  
}

void translateVtg() {
    // Does nothing
}

void sendToRadio(String outputMsg) {
  radioSerial.print(outputMsg);
  debugSerial.print("uC->RADIO: ");
  debugSerial.println(outputMsg);
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

