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



// Adjust according to module ID
#define OWN_ID     00
#define BAUD_RATE  9600

#define ANSWER       true
#define MAX_LENGTH   16
#define LINE_ENDING  ";\r\n"



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
pm | pin mode
dw | digital write
aw | analog write
dr | digital read
ar | analog read
al | all

*******************************************************************************/



#define OFFSET_ID   0
#define OFFSET_CMD  2
#define OFFSET_AR1  4
#define OFFSET_AR2  8
#define SIZE_ARG  4


template<class T> inline Print &operator << (Print &obj, T arg) { obj.print(arg); return obj; }


String command = String();
int CALL_ID = -1;


void setup() {
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
  // check device id
  if (isNumeric(command.charAt(0)) && isNumeric(command.charAt(1)))
    CALL_ID = getIntArgument(0, 2);
  if (CALL_ID != -1 && CALL_ID == OWN_ID) {
    // pm - pin mode
    if (command.charAt(2) == 'p' && command.charAt(3) == 'm')
      pinModeFunc();
    // dw - digital write
    if (command.charAt(2) == 'd' && command.charAt(3) == 'w')
      digitalWriteFunc();
    // aw - analog write
    if (command.charAt(2) == 'a' && command.charAt(3) == 'w')
      analogWriteFunc();
    // al - all
    if (command.charAt(2) == 'a' && command.charAt(3) == 'l')
      allFunc();
  }
  // clear buffer
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
