/**
 * String manipulation functions
 */

#include "Arduino.h"
#include "string_manip.h"
 
/**
 * Left-hand pads a number with zeros to reach a desired length
 */
char *leftPadNumber(char *input, int targetLength) {
  int inputLength = strlen(input);
  int offset = 0;
  char *output = (char*)calloc(targetLength + 1, sizeof(char));
  boolean negative = false;
  if(input[0] == '-') {
    output[0] = '-';
    offset = 1;
    negative = true;
  }
  int paddingSize = targetLength - inputLength;
  for(int i = 0 ; i < paddingSize ; i++) {
    output[i + offset] = '0';
  }
  if(negative) {
    strcat(output, input + 1);
  } else {
    strcat(output, input);
  }
  return output;
}
