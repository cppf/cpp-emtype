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


void setup()
{
  Serial.begin(57600);
}

void loop()
{
  Serial.println(ToByte(1, 1));
}

