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

void allFunc(){
  if(getArgument(AR1).equals(" LOW")){
    for(int i = 0; i < 14; i++){
      digitalWrite(i, LOW);
    }
  }
  if(getArgument(AR1).equals("HIGH")){
    for(int i = 0; i < 14; i++){
      digitalWrite(i, HIGH);
    }
  }
  if(getArgument(AR1).equals("OUTP")){
    for(int i = 0; i < 14; i++){
      pinMode(i, OUTPUT);
    }
  }
  if(getArgument(AR1).equals("INPU")){
    for(int i = 0; i < 14; i++){
      pinMode(i, INPUT);
    }
  }
  if(answer){
    Serial << "-" << ownID << "- al " << getArgument(AR1) << "\n";
  }
}
