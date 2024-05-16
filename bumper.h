//code related to the bumper switch on the front of the vacuum



#ifndef BUMPER_H
#define BUMPER_H

//this function is triggered when the bumper switch detects a collison
void bump()
{
  byte done = 0;
  unsigned long tb = millis();
  
  //immediatelly kill the motors 
  writemotor1(0);
  writemotor2(0);
  m1throtA = 0;
  m2throtA = 0;
  
  while(!done)
  {
    //go straight backwards briefly
    m1throtT = -100*speedlim;
    m2throtT = -100*speedlim;
    adjustmotor1(m1throtT);
    adjustmotor2(m2throtT);
    
    if((millis()-tb)>(750/speedlim))  //see if you've been going backwards for long enough 
    {
      done = 1;
      while(!((m1throtA == 0)&&(m2throtA == 0)))  //wait until both motors ramp back to zero
      {
        m1throtT = 0;
        m2throtT = 0;
        adjustmotor1(m1throtT);
        adjustmotor2(m2throtT);
      }
    }
  }
  
  unsigned long tb2 = millis();
  done = 0;
  
  //randomly pick a direction to rotate in
  byte dr = random(2);
  int drval = 0;
  if(dr == 0)
  {
    drval = 1;
  }
  else
    drval = -1;

  while(!done)
  {
    m1throtT = 100*drval*speedlim;
    m2throtT = -100*drval*speedlim;
    adjustmotor1(m1throtT);
    adjustmotor2(m2throtT);
    
    if((millis()-tb2)>(((1200/speedlim))*random(5, 16)*0.1))  //turn a random amount of time
    {
      done = 1;
      while(!((m1throtA == 0)&&(m2throtA == 0)))  //wait until both motors ramp back to zero
      {
        m1throtT = 0;
        m2throtT = 0;
        adjustmotor1(m1throtT);
        adjustmotor2(m2throtT);
      }
    }    
  }
}


//this function just sees if the switch is triggered, then runs the bump function. Logic causes bump() to occur only once, even if the switch is held down
void checksw()
{
  bs = digitalRead(bspin);  
  if((bs == 0)&&(bslast == 1))
    {bump();}
  bslast = bs;
}


#endif