/*
  ==============================================================================

    Granulator.h
    Created: 23 Jan 2016 3:15:56pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef GRANULATOR_H_INCLUDED
#define GRANULATOR_H_INCLUDED

class Granulator
{
public:
    Granulator();
    ~Granulator();
    
    float process(float input);

private:
    //if state is zero, no stretch, if state is 1, stretching
    bool state;
};



#endif  // GRANULATOR_H_INCLUDED
