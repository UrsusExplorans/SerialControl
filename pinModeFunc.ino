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

void pinModeFunc(){
  int pin = parseArgument(AR1);
  if(getArgument(AR2).equals("INPU")){
    pinMode(pin, INPUT);
    if(answer){
      Serial << "-" << ownID << "- pm " << pin << " INPUT" << "\n";
    }
  } else {
    if(getArgument(AR2).equals("OUTP")){
      pinMode(pin, OUTPUT);
      if(answer){
        Serial << "-" << ownID << "- pm " << pin << " OUTPUT" << "\n";
      }
    } else {
      // error
    }
  }
}
