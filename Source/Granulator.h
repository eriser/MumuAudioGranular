/*
  ==============================================================================

    Granulator.h
    Created: 23 Jan 2016 3:15:56pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef GRANULATOR_H_INCLUDED
#define GRANULATOR_H_INCLUDED

#include "Grain.h"
#include "GranularBuffer.h"

class Granulator
{
public:
    Granulator();
    ~Granulator();
    
    float process(float input, Grain* grains, GranularBuffer &buffer, bool buttonState, bool schedulerBang, float numGrains, float sampleRate, float grainSize, float pitch, float stretchSpeed);

private:
    //if state is zero, no stretch, if state is 1, stretching
    bool state;
    
    float stretchDelta;
    
    bool stretchStarted;
};



#endif  // GRANULATOR_H_INCLUDED
