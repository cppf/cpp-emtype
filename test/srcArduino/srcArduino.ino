/*
----------------------------------------------------------------------------------------
    emType: Testing and debugging source code (Arduino)
    File: srcArduino.ino

    This file is part of emType. For more details, go through
    Readme.txt. For copyright information, go through copyright.txt.

    emType is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    emType is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with emType.  If not, see <http://www.gnu.org/licenses/>.
----------------------------------------------------------------------------------------
*/

#include "emType.h"

int Data[256];

void setup()
{
  // start serial
  Serial.begin(57600);
  // capture start time
  long Time_Start = micros();
  // loop for type conversion
  for(byte i=0; i<255; i++)
  {
    // Data[i] = (i << 8) | (i + 1);
    Data[i] = ToInt(i, i + 1);
  }
  // capture stop time
  long Time_Stop = micros();
  // display time taken
  Serial.print("Time (in us): ");
  Serial.println(Time_Stop - Time_Start);
}

void loop()
{
  // just wait
  delay(1000);
}

