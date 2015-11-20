/*
  ==============================================================================

    Grain.h
    Created: 31 Oct 2015 4:48:35pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef GRAIN_H_INCLUDED
#define GRAIN_H_INCLUDED

#include "GranularBuffer.h"
#include "TukeyWindow.h"
#include "FourPointInterpolate.h"

class Grain
{
public:
    Grain();
    ~Grain();
    void setDelta(float sampleRate, float seconds);
    void setWindowSize(int sampleRate, float seconds);
    void init(float pitch, GranularBuffer& buffer);
    int isItBusy();
    float play(int sampleRate, GranularBuffer& buffer);
    int returnIncrementer();
    
    int isBusy;
private:
    TukeyWindow Window;
    float m_nDelta;
    float m_fWindowSize;
    
    float grainIndex;
    int grainIndex_f1;
    int grainIndex_f2;
    int grainIndex_p1;
    
    float bufferSpeed;
    
    
};



#endif  // GRAIN_H_INCLUDED
