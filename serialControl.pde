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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <WString.h>

template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define maxLength 16

/* Command structure:
pos:  01 23 4567 8901 23456
      id cm arg1 arg2
*/

// Corresponding offests:
#define ID  0
#define CMD 2
#define AR1 4
#define AR2 8

int ownID = 0; // Adjust according to module ID
boolean answer = true;

String command = String(maxLength);
boolean commandComplete = false;
int recID;

void setup() {
  Serial.begin(9600);
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
  if(inChar == 59 || inChar == 10 || inChar == 13){
    commandComplete = true;
  } else {
    command.append(inChar);
  }
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

boolean isNumeric(char character){
  boolean ret = false;
  if(character >= 48 && character <= 75){
    ret = true;
  }
  return true;
}

String getArgument(int argOffset){
  return command.substring(argOffset, argOffset + 4);
}
