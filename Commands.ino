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


// scan for device id's
void scanFunc() {
  delay( SCAN_DELAY * (OWN_ID + 2) );
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "id" << VERSION << LINE_ENDING;
#endif
}


// all pins
void allFunc() {
  String arg = getArgument(OFFSET_AR1, SIZE_ARG);
  arg.toUpperCase();
  if (getArgument(OFFSET_AR1, SIZE_ARG - 1).equals("LOW"))
    arg = "LOW_";
  // set all to output mode off/low
  if (arg.equals("OUTP") || arg.equals("LOW_")) {
    for (int i = PIN_FROM; i < PIN_TO; i++) {
      pinMode     (i, OUTPUT);
      digitalWrite(i, LOW);
    }
  } else
  // set all to output mode on/high
  if (arg.equals("HIGH")) {
    for (int i = PIN_FROM; i < PIN_TO; i++) {
      pinMode     (i, OUTPUT);
      digitalWrite(i, HIGH);
    }
  } else
  // set all to input mode
  if (arg.equals("INPU")) {
    for (int i = PIN_FROM; i < PIN_TO; i++)
      pinMode(i, INPUT);
  } else
  // set all to input pulled high mode
  if (arg.equals("INHI")) {
    for (int i = PIN_FROM; i < PIN_TO; i++)
      pinMode(i, INPUT_PULLUP);
  } else {
    // error
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "ERROR" << LINE_ENDING;
#endif
    return;
  }
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "al" << arg << LINE_ENDING;
#endif
}


// set pin mode
void pinModeFunc() {
  int    pin  = getIntArgument(OFFSET_AR1, SIZE_ARG);
  String mode = getArgument   (OFFSET_AR2, SIZE_ARG);
  mode.toUpperCase();
  // set output mode
  if (mode.equals("OUTP")) {
    pinMode     (pin, OUTPUT);
    digitalWrite(pin, LOW);
  } else
  // set input floating mode
  if (mode.equals("INPU")) {
    pinMode     (pin, INPUT);
    digitalWrite(pin, LOW);
  } else
  // set input pulled high
  if (mode.equals("INHI")) {
    pinMode     (pin, INPUT_PULLUP);
    //digitalWrite(pin, HIGH);
  } else {
    // error
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "ERRORpm" << LINE_ENDING;
#endif
    return;
  }
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "pm" << padInt(pin, SIZE_ARG) << mode << LINE_ENDING;
#endif
}


// digital write
void digitalWriteFunc() {
  int  pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  char arg = command.charAt(OFFSET_AR2);
  // set pin high
  if (arg == '1' || arg == 'H' || arg == 'h') {
    digitalWrite(pin, HIGH);
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "dw" << padInt(pin, SIZE_ARG) << "HIGH" << LINE_ENDING;
#endif
  } else
  // set pin low
  if (arg == '0' || arg == 'L' || arg == 'l') {
    digitalWrite(pin, LOW);
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "dw" << padInt(pin, SIZE_ARG) << "LOW_" << LINE_ENDING;
#endif
  } else {
    // error
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "ERRORdw" << LINE_ENDING;
#endif
  }
}


void analogWriteFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  int val = getIntArgument(OFFSET_AR2, SIZE_ARG);
  // set pwm
  analogWrite(pin, val);
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "aw" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void digitalReadFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // read digital
  int val = digitalRead(pin);
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "dr" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void analogReadFunc() {
  int pin = getIntArgument(OFFSET_AR1, SIZE_ARG);
  // read analog
  int val = analogRead(pin);
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "ar" << padInt(pin, SIZE_ARG) << padInt(val, SIZE_ARG) << LINE_ENDING;
#endif
}


void setIdFunc() {
  int id = getIntArgument(OFFSET_AR1, SIZE_ARG);
  if (id < 0 || id > 99) {
#ifdef ANSWER
    Serial << padInt(OWN_ID, SIZE_ID) << "ERRORid" << LINE_ENDING;
#endif
    return;
  }
  // save to flash
#if defined ( is_AVR )
  EEPROM.write(MEMADDR_ID, id);
#elif defined ( is_SAM )
  DueFlashStorage().write(MEMADDR_ID, (byte) id);
#endif
  OWN_ID = id;
#ifdef ANSWER
  Serial << padInt(OWN_ID, SIZE_ID) << "id" << LINE_ENDING;
#endif
}
