/**
 * String manipulation functions
 */

#include "Arduino.h"
#include "string_manip.h"
 
/**
 * Left-hand pads a number with zeros to reach a desired length
 */
String leftPadNumber(String input, int targetLength) {  
  String tmp = "";
  boolean negative = false;
  if(input.charAt(0) == '-') {
    tmp += '-';
    negative = true;
  }
  for(int i = input.length() ; i < targetLength ; i++) {
    tmp += '0';
  }
  if(negative) {
    tmp += input.substring(1);
  } else {
    tmp += input;
  }
  return tmp;
}