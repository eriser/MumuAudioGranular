/*
  ==============================================================================

    Granulator.cpp
    Created: 23 Jan 2016 3:15:56pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "Granulator.h"
#include <math.h>

//==============================================================================
Granulator::Granulator(){
    
}

//==============================================================================
Granulator::~Granulator(){
    
}

//==============================================================================
float Granulator::process( Grain* grains, GranularBuffer &buffer, bool buttonState, bool schedulerBang, float numGrains, float sampleRate, float grainSize, float pitch, float stretchSpeed){
    
    if (buttonState == 0)
    {
        stretchStarted = false;
        if (schedulerBang == true)
        {
            for (int i = 0; i < numGrains; i++)
            {
                if(grains[i].isItBusy() == 0)
                {
                    grains[i].setWindowSize(sampleRate, grainSize);
                    float delta = 0;
                    if (pitch > 1)
                    {
                        delta = (pitch-1)*(grainSize*sampleRate);
                    }
                    grains[i].setDelta(sampleRate, delta);
                    grains[i].init(pitch, buffer);
                    grains[i].isBusy = 1;
                    break;
                }
            }
        }
    }
    if (buttonState == 1)
    {
        if (stretchStarted == false)
        {
            stretchDelta = 0;
            stretchStarted = true;
        }
        stretchDelta = fmod((stretchDelta + stretchSpeed), buffer.getBufferLength());
        if (schedulerBang == true)
        {
            for (int i = 0; i < numGrains; i++)
            {
                if(grains[i].isItBusy() == 0)
                {
                    grains[i].setWindowSize(sampleRate, grainSize);
                    grains[i].setDelta(sampleRate, stretchDelta);
                    grains[i].init(pitch, buffer);
                    grains[i].isBusy = 1;
                    break;
                }
            }
        }
    }
    float output = 0;
    for (int i = 0; i < numGrains; i++)
    {
        output += grains[i].play(sampleRate, buffer);
    }
    return output;
}