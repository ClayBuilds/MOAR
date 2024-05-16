//miscellaneous functions that don't fit elsewhere, mostly for testing purposes


#ifndef MISCFUNCS_H
#define MISCFUNCS_H



//This function prints the analog stick readings from the controller for debugging
void printcontroller()
{
  Serial.print("LX: ");
  Serial.print(LX);
  Serial.print("  LY: ");
  Serial.print(LY);
  Serial.print("  RX: ");
  Serial.print(RX);
  Serial.print("  RY: ");
  Serial.print(RY);
  Serial.print("  CONTROLLER: ");
  Serial.println(haveController);
}

//this function prints an array of 16 values, with each number corresponding to the button press of that index
void printbuts()
{
  for(byte i = 0; i<16; ++i)
  {
    Serial.print("  ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(BUTTNUMS[i]);
  }
  Serial.println(" ");
}

//prints actual motor pwm signal value and target throttle (%)
void printmotvals()
{
  Serial.print("LEFT MOTOR (1): Throttle: ");
  Serial.print(m1throtT);
  Serial.print(" PWM actual: ");
  Serial.print(m1pwmA);
  
  Serial.print("     RIGHT MOTOR (2): Throttle: ");
  Serial.print(m2throtT);
  Serial.print(" PWM actual: ");
  Serial.print(m2pwmA);
  
  Serial.println(" ");
}

//print switch state
void printsw()
{
  Serial.print("SWITCH: ");
  Serial.println(bs);
}

#endif