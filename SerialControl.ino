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


template<class T> inline Print &operator << (Print &obj, T arg) { obj.print(arg); return obj; }

#define maxLength 16
#define LINE_ENDING ";\r\n"
#define BAUD_RATE  9600

#define MAX_LENGTH   16


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



// Corresponding offests:
#define ID  0
#define CMD 2
#define AR1 4
#define AR2 8

int ownID = 0; // Adjust according to module ID
boolean answer = true;

String command = String(MAX_LENGTH);
boolean commandComplete = false;
int recID;

void setup() {
  Serial.begin(BAUD_RATE);
  recID = 0;
  command = "00alOUTP";
  allFunc();
  command = "00al LOW";
  allFunc();
  command = "";
}

void loop () {
  if(Serial.available() > 0) {
    getIncomingChars();
  }

  if (commandComplete == true) {
    processCommand();
  }

}

void getIncomingChars() {
  char inChar = Serial.read();
  for(int i = 0; i < sizeof(LINE_ENDING); i++) {
    if(LINE_ENDING[i] == inChar) {
      commandComplete = true;
      return;
    }
  }
  command += inChar;
}

void processCommand(){
  if(commandCorrect() && (recID == ownID)){
    if(command.charAt(2) == 'p' && command.charAt(3) == 'm'){ // pin mode
      pinModeFunc();
    }

    if(command.charAt(2) == 'd' && command.charAt(3) == 'w'){ // digital write
      digitalWriteFunc();
    }

    if(command.charAt(2) == 'a' && command.charAt(3) == 'w'){ // analog write
      analogWriteFunc();
    }

    if(command.charAt(2) == 'a' && command.charAt(3) == 'l'){ // all
      allFunc();
    }

  }
  
  command = "";
  recID = 0;
  commandComplete = false;
}

boolean commandCorrect(){
  boolean ret = false;
  if(command.charAt(0) == '0' || command.charAt(0) == '1'){
    if(isNumeric(command.charAt(1))){
      recID = command.charAt(1) - 48;
      if(command.charAt(0) == '1'){ recID = recID + 10; }
      ret = true;
    }
  }
  return ret;
}

int parseArgument(int argOffset){
  int ret = 0;
  String arg = command.substring(argOffset, argOffset + 4);
  if(isNumeric(arg.charAt(3))){
    ret = arg.charAt(3) - 48;
    if(isNumeric(arg.charAt(2))){
      ret = ret + (10 * (arg.charAt(2) - 48));
      if(isNumeric(arg.charAt(1))){
        ret = ret + (100 * (arg.charAt(1) - 48));
        if(arg.charAt(0) == '-'){
          ret = -ret;
        } else {
          if(isNumeric(arg.charAt(0))){
            ret = ret + (1000 * (arg.charAt(0) - 48));
          }
        }
      }
    }
  }
  return ret;
}

boolean isNumeric(char character) {
  return (character >= '0' && character <= '9');
}

String getArgument(int argOffset){
  return command.substring(argOffset, argOffset + 4);
}
