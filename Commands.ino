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


void allFunc() {
  // set all off/low
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("_LOW")) {
    for (int i = 2; i < 14; i++)
      digitalWrite(i, LOW);
  } else
  // set all on/high
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("HIGH")) {
    for (int i = 2; i < 14; i++)
      digitalWrite(i, HIGH);
  } else
  // set all to output mode
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("OUTP")) {
    for (int i = 2; i < 14; i++)
      pinMode(i, OUTPUT);
  } else
  // set all to input mode
  if (getArgument(OFFSET_AR1, SIZE_ARG).equals("INPU")) {
    for (int i = 2; i < 14; i++)
      pinMode(i, INPUT);
  }
#ifdef ANSWER
  Serial << padInt(OWN_ID, 2) << "al" << getArgument(OFFSET_AR1, SIZE_ARG) << LINE_ENDING;
#endif
}


void pinModeFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // set mode input
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("INHI")) {
    pinMode     (pin, INPUT_PULLUP);
    //digitalWrite(pin, HIGH);
#ifdef ANSWER
    Serial << padInt(OWN_ID, 2) << "pm" << padInt(pin, SIZE_ARG) << "INHI" << LINE_ENDING;
#endif
    return;
  }
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("INPU")) {
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
#ifdef ANSWER
    Serial << padInt(OWN_ID, 2) << "pm" << padInt(pin, SIZE_ARG) << "INPU" << LINE_ENDING;
#endif
    return;
  }
  // set mode output
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("OUTP")) {
    digitalWrite(pin, LOW);
    pinMode     (pin, OUTPUT);
#ifdef ANSWER
    Serial << padInt(OWN_ID, 2) << "pm" << padInt(pin, SIZE_ARG) << "OUTP" << LINE_ENDING;
#endif
    return;
  }
  // error
#ifdef ANSWER
  Serial << "ERROR" << LINE_ENDING;
#endif
}


void digitalWriteFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // set output on/high
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("HIGH")) {
    digitalWrite(pin, HIGH);
#ifdef ANSWER
    Serial << padInt(OWN_ID, 2) << "dw" << padInt(pin, SIZE_ARG) << "HIGH" << LINE_ENDING;
#endif
    return;
  }
  // set output off/low
  if (getArgument(OFFSET_AR2, SIZE_ARG).equals("_LOW")) {
    digitalWrite(pin, LOW);
#ifdef ANSWER
    Serial << padInt(OWN_ID, 2) << "dw" << padInt(pin, SIZE_ARG) << "_LOW" << LINE_ENDING;
#endif
    return;
  }
  // error
#ifdef ANSWER
  Serial << "ERROR" << LINE_ENDING;
#endif
}


void analogWriteFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  int val = getIntArgument(OFFSET_AR2, SIZE_ARG);
  // set pwm
  analogWrite(pin, val);
#ifdef ANSWER
  Serial << padInt(OWN_ID, 2) << "aw" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void digitalReadFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // read digital
  int val = digitalRead(pin);
#ifdef ANSWER
  Serial << padInt(OWN_ID, 2) << "dr" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void analogReadFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // read analog
  int val = analogRead(pin);
#ifdef ANSWER
  Serial << padInt(OWN_ID, 2) << "ar" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void setIdFunc() {
  int id = getIntArgument(OFFSET_AR1, SIZE_ARG);
  if (id < 0 || id > 99) {
#ifdef ANSWER
    Serial << "OUTOFRANGE" << LINE_ENDING;
#endif
    return;
  }
  EEPROM.write(MEM_ID, id);
  OWN_ID = id;
#ifdef ANSWER
  Serial << padInt(OWN_ID, 2) << "id" << LINE_ENDING;
#endif
}
