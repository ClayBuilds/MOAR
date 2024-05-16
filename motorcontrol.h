//code for sending pwm values to the motors


#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

void writemotor1(int p)  //takes a throttle value in percent (from -100 to +100) then writes the motor pwm and direction accordingly 
{
  int d = 0;
  if(p>=0)    //determine direction
  {d = 1;}
  
  p = abs(p);
  int pwm = map(p, 0, 100, 0, 255); //determine magnitude
  
  if(d)                               //set direction
    {
      digitalWrite(m1Apin, HIGH);
      digitalWrite(m1Bpin, LOW);
    }
  else
    {
      digitalWrite(m1Apin, LOW);
      digitalWrite(m1Bpin, HIGH);
    }
  
  pwm = constrain(pwm, 0, 255); //safety in case fuckup upstream
  
  analogWrite(m1pwmpin, pwm);   //set magnitude
  m1pwmA = pwm;   //track pwm
}

void writemotor2(int p)  //takes a throttle value in percent (from -100 to +100) then writes the motor pwm and direction accordingly 
{
  int d = 0;
  if(p>=0)    //determine direction
  {d = 1;}
  
  p = abs(p);
  int pwm = map(p, 0, 100, 0, 255); //determine magnitude
  
  if(d)                               //set direction (NOTE: logic reversed compared to motor 1 because it's physically mounted backwards)
    {
      digitalWrite(m2Apin, LOW);
      digitalWrite(m2Bpin, HIGH);
    }
  else
    {
      digitalWrite(m2Apin, HIGH);
      digitalWrite(m2Bpin, LOW);
    }
  
  pwm = constrain(pwm, 0, 255); //safety in case fuckup upstream
  
  analogWrite(m2pwmpin, pwm);   //set magnitude
  m2pwmA = pwm;   //track pwm
}



void adjustmotor1(int targ)   //gradually ramp motor speed up or down towards target
{
  targ = constrain(targ, -100, 100);
  
  if((millis()-m1tlast)<m1adjtime) //see if enough time has passed since last adjustment
  {return;}
  else
  {m1tlast= millis();}

  if(m1throtA>targ)         //ramp down
  {
    writemotor1(m1throtA-m1adjval);       
    m1throtA = m1throtA-m1adjval;
  }
  else if(m1throtA<targ)    //ramp up
  {
    writemotor1(m1throtA+m1adjval);
    m1throtA = m1throtA+m1adjval;
  }
  else
  {writemotor1(m1throtA);}   //stay the same
  
  if(abs(m1throtA-targ)<=m1adjval)   //if its within the adjutment threshhold, write it directly to the target speed
  {
    writemotor1(targ);
    m1throtA = targ;
  }
}

void adjustmotor2(int targ)   //gradually ramp motor speed up or down towards target
{
  targ = constrain(targ, -100, 100);
  
  if((millis()-m2tlast)<m2adjtime) //see if enough time has passed since last adjustment
  {return;}
  else
  {m2tlast= millis();}

  if(m2throtA>targ)         //ramp down
  {
    writemotor2(m2throtA-m2adjval);       
    m2throtA = m2throtA-m2adjval;
  }
  else if(m2throtA<targ)    //ramp up
  {
    writemotor2(m2throtA+m2adjval);
    m2throtA = m2throtA+m2adjval;
  }
  else
  {writemotor2(m2throtA);}   //stay the same
  
  if(abs(m2throtA-targ)<=m2adjval)   //if its within the adjutment threshhold, write it directly to the target speed
  {
    writemotor2(targ);
    m2throtA = targ;
  }
}

void mapTargets() //set target throttles for each motor depending on input received from ps2 controller
{
  if(!haveController) //ramp down to zero if controller connection is lost
  {
    m1throtT = 0;
    m2throtT = 0;
  }
  else
  {
    
    //This uses "Tank style" steering with the y axis of left and right sticks for left and right motors

    if((abs(LY-128))<7)   //set to midpoint if it's close, fixes "stick drift" where the analog sticks don't quite center at zero
    {LY = 128;}
    if((abs(RY-128))<7)
    {RY = 128;}
    
    int val1 = map(LY, 0, 255, 100, -100);  
    int val2 = map(RY, 0, 255, 100, -100);
    
    val1 = constrain(val1, -100, 100);  //safety in case of upstream fuckup
    val2 = constrain(val2, -100, 100);
    
    m1throtT = val1;
    m2throtT = val2;
   
  }
}
#endif