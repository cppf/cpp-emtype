/*
 *  ------Waspmote Sensors Analog Inputs Example--------
 *
 *  Explanation: This example shows how to read the analog inputs
 *  available in Waspmote
 *
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:                0.1
 *  Design:                 David Gascón
 *  Implementation:    Alberto Bielsa
 */
 
 
void setup()
{
  // Init USB
  USB.begin();
  
  // Setting Digital 1 as an output
  pinMode(DIGITAL1,OUTPUT);
}

void loop()
{
  // Getting Value from Analog Input
  USB.print("Value read from Analog 4: ");
  USB.println(analogRead(ANALOG4),DEC);
  
  // Writing a value to DIGITAL1. This is a digital/analog input/output.
  //  It is the only analog pin which can be written.
  analogWrite(DIGITAL1,128);
}


