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


void allFunc(){
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("_LOW")) {
    for(int i = 0; i < 14; i++){
      digitalWrite(i, LOW);
    }
  }
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("HIGH")) {
    for(int i = 0; i < 14; i++){
      digitalWrite(i, HIGH);
    }
  }
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("OUTP")) {
    for(int i = 0; i < 14; i++){
      pinMode(i, OUTPUT);
    }
  }
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("INPU")) {
    for(int i = 0; i < 14; i++){
      pinMode(i, INPUT);
    }
  }
#ifdef ANSWER
  Serial << "-" << OWN_ID << "- al " << getArgument(OFFSET_AR1, SIZE_ARG) << LINE_ENDING;
#endif
}


void pinModeFunc(){
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("INPU")) {
    pinMode(pin, INPUT);
#ifdef ANSWER
    Serial << "-" << OWN_ID << "- pm " << pin << " INPUT" << LINE_ENDING;
#endif
  } else {
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("OUTP")) {
      pinMode(pin, OUTPUT);
    } else {
      // error
    }
#ifdef ANSWER
    Serial << "-" << OWN_ID << "- pm " << pin << " OUTPUT" << LINE_ENDING;
#endif
  }
}


void digitalWriteFunc(){
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("HIGH")) {
    digitalWrite(pin, HIGH);
#ifdef ANSWER
    Serial << "-" << OWN_ID << "- dw " << pin << " HIGH" << LINE_ENDING;
#endif
  } else {
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("_LOW")) {
      digitalWrite(pin, LOW);
    } else {
      // error
    }
  }
#ifdef ANSWER
    Serial << "-" << OWN_ID << "- dw " << pin << "_LOW" << LINE_ENDING;
#endif
}


void analogWriteFunc(){
  int pin   = getIntArgument(OFFSET_AR1, SIZE_ARG);
  int value = getIntArgument(OFFSET_AR2, SIZE_ARG);
  analogWrite(pin, value);
#ifdef ANSWER
  Serial << "-" << OWN_ID << "- aw " << pin << " " << value << LINE_ENDING;
#endif
}
