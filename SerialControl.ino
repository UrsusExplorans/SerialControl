/*******************************************************************************

    This file is part of SerialControl.

    SerialControl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    SerialControl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SerialControl.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/



// Adjust according to module ID - uncomment to override eeprom value
//#define  FORCE_ID     00  // 0 to 99  (comment this line to use eeprom/flash)
#define  BAUD_RATE    9600
#define  ANSWER       true
#define  SCAN_DELAY   20

#define  MAX_LENGTH   16
#define  LINE_ENDING  ";\r\n"

#define  PIN_FROM     2
#define  PIN_TO       14



/*******************************************************************************

Command Structure
=================
pos: 12 34 5678 9012 345
     ID CM ARG1 ARG2 ;RN
     01 23 4567 8901 234

  ID | device id
  CM | command
ARG1 | argument 1
ARG2 | argument 2
  RN | end of line

Commands
========
scan | request id number from all connected devices
pm | pin mode
dw | digital write
aw | analog write
dr | digital read
ar | analog read
al | all pins
id | set the device id within eeprom

Pin Modes
=========
OUTP | output mode (io or pwm)
INPU | input mode (floating, external resistor)
INHI | input mode (pulled high internally)

*******************************************************************************/


#include <EEPROM.h>


// eeprom address locations
#define MEM_ID  11

// packet sections
#define OFFSET_ID   0
#define OFFSET_CMD  2
#define OFFSET_AR1  4
#define OFFSET_AR2  8
#define SIZE_ARG    4


template<class T> inline Print &operator << (Print &obj, T arg) { obj.print(arg); return obj; }


int OWN_ID = 0;

String command = String();
int CALL_ID = -1;


void setup() {
#ifdef FORCE_ID
  // override device id
  OWN_ID = FORCE_ID;
#else
  // load device id from eeprom
  OWN_ID = EEPROM.read(MEM_ID);
#endif
  Serial.begin(BAUD_RATE);
  command = "##alOUTP";
  allFunc();
  command = "##al_LOW";
  allFunc();
  command = "";
}


void loop () {
  if (Serial.available() > 0)
    getIncomingChars();
}


void getIncomingChars() {
  char inChar = Serial.read();
  for (int i = 0; i < sizeof(LINE_ENDING); i++) {
    if (LINE_ENDING[i] == inChar) {
      processCommand();
      return;
    }
  }
  command += inChar;
}


void processCommand() {
  if (command.length() == 0) {
    Serial << "\r\n";
    clearBuffer();
    return;
  }
  // scanning for device id's
  if (command.charAt(0) == 's' && command.charAt(1) == 'c' && command.charAt(2) == 'a' && command.charAt(3) == 'n') {
    delay(SCAN_DELAY * (OWN_ID + 1) );
    Serial << padInt(OWN_ID, 2) << "scan" << LINE_ENDING;
    clearBuffer();
    return;
  }
  // check device id
  if (isNumeric(command.charAt(0)) && isNumeric(command.charAt(1)))
    CALL_ID = getIntArgument(0, 2);
  if (CALL_ID == -1) {
    Serial << "ERROR" << LINE_ENDING;
    clearBuffer();
    return;
  }
  if (CALL_ID != OWN_ID) {
    clearBuffer();
    return;
  }
  // pm - pin mode
  if (command.charAt(2) == 'p' && command.charAt(3) == 'm')
    pinModeFunc();
  else
  // dw - digital write
  if (command.charAt(2) == 'd' && command.charAt(3) == 'w')
    digitalWriteFunc();
  else
  // aw - analog write
  if (command.charAt(2) == 'a' && command.charAt(3) == 'w')
    analogWriteFunc();
  else
  // dr - digital read
  if (command.charAt(2) == 'd' && command.charAt(3) == 'r')
    digitalReadFunc();
  else
  // ar - analog read
  if (command.charAt(2) == 'a' && command.charAt(3) == 'r')
    analogReadFunc();
  else
  // al - all
  if (command.charAt(2) == 'a' && command.charAt(3) == 'l')
    allFunc();
  else
  if (command.charAt(2) == 'i' && command.charAt(3) == 'd')
    setIdFunc();
  else
    Serial << "UNKNOWN" << LINE_ENDING;
  clearBuffer();
}
void clearBuffer() {
  command = "";
  CALL_ID = -1;
}


boolean isNumeric(char character) {
  return (character >= '0' && character <= '9');
}


int getIntArgument(int offset, int width) {
  int val = 0;
  for (int i = offset; i < offset + width; i++) {
    if(isNumeric(command.charAt(i))) {
      val *= 10;
      val += (command.charAt(i) - '0');
    }
  }
  return val;
}


String getArgument(int offset, int width) {
  return command.substring(offset, offset + width);
}


String padInt(int val, byte width) {
  String buf = String();
  int pow = 1;
  for (byte b = 1; b < width; b++) {
    pow *= 10;
    if(val < pow)
      buf += '0';
  }
  return buf + val;
}
