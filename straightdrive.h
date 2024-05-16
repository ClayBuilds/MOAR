//this handles nominal driving across a room when it isn't hitting anything

#ifndef STRAIGHTDRIVE_H
#define STRAIGHTDRIVE_H

//considered future addition of some random veering off course here instead of constant straight speed
//kept it simple for now
void straight()
{
  m1throtT = 100*speedlim;
  m2throtT = 100*speedlim;
  adjustmotor1(m1throtT);
  adjustmotor2(m2throtT);
}

#endif