#include "Embedded_Type.h"

void always()
{
  // Getting Value from Analog Input
  // USB.print("Value read from Analog 4: ");
  // USB.println(analogRead(ANALOG4),DEC);
  USB.println(ToByte(1, 1));
  // Writing a value to DIGITAL1. This is a digital/analog input/output.
  //  It is the only analog pin which can be written.
  analogWrite(DIGITAL1,128);

}

