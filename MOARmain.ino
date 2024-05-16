//program for control of vacuum robot
// 5-15-24
// Clay M


#include "pinout.h"
#include "miscvars.h"
#include "motorcontrol.h"
#include "ps2.h"
#include "miscfuncs.h"
#include "bumper.h"
#include "straightdrive.h"

void setup() 
{
  //set all pins for drive control to output
  pinMode(m1Apin, OUTPUT);
  pinMode(m1pwmpin, OUTPUT);
  pinMode(m1Bpin, OUTPUT);
  pinMode(m2Apin, OUTPUT);
  pinMode(m2pwmpin, OUTPUT);
  pinMode(m2Bpin, OUTPUT);
  
  //set bumper switch pin
  pinMode(bspin, INPUT_PULLUP);
  
  //start with the motors off
  digitalWrite(m1Apin, LOW);
  digitalWrite(m1Bpin, LOW);
  digitalWrite(m2Apin, LOW);
  digitalWrite(m2Bpin, LOW);
  
  //ps2 controller stuff
  fastPinMode (PIN_BUTTONPRESS, OUTPUT);
	fastPinMode (PIN_HAVECONTROLLER, OUTPUT);
	delay (300);
	Serial.begin (115200);
	Serial.println (F("Ready!"));
  
  
}

void loop() 
{
  
  //if there's a controller plugged in, drive manually. otherwise use the auto functions.
  checkcontroller();
  if(!haveController)
  {
    checksw();
    straight();
  }

  //uncomment below functions onlyu for testing and troubleshooting
  
  //printcontroller();    //rapidly prints analog stick values from controller
  //printbuts();          //rapidly prints integer values 1-16 corresponding to which digital buttons on ps2 controller are pressed
  //printmotvals();       //rapidly prints throttle values to each motor and actual pwm duty cycle being fed to each
  //printsw();            //rapidly prints value read from the bumper switch

}


