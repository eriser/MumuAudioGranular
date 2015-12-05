/*
  ==============================================================================

    Grain.cpp
    Created: 31 Oct 2015 4:48:35pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "Grain.h"
#include <iostream>

Grain::Grain(){
    isBusy = 0;
    grainIndex = 0;
}

Grain::~Grain(){
    
}

void Grain::setDelta(float sampleRate, float samples){
    m_nDelta = samples;
}

void Grain::setWindowSize(int sampleRate, float seconds){
    Window.setWindowLength(sampleRate, seconds);
}

void Grain::init(float pitch, GranularBuffer& buffer){
    bufferSpeed = pitch;
    
    grainIndex = buffer.nWriteIndex - m_nDelta;
    if (grainIndex < 0)
    {
        grainIndex += buffer.nBufferSize;
    }
    if (grainIndex > buffer.nBufferSize)
    {
        grainIndex -= buffer.nBufferSize;
    }
}

int Grain::isItBusy(){
    return isBusy;
}

float Grain::play(int sampleRate, GranularBuffer& buffer){
    float yn = buffer.pBuffer[(int)grainIndex % buffer.nBufferSize];
    float yn_f1 = buffer.pBuffer[((int)grainIndex+1) % buffer.nBufferSize];
    float yn_f2 = buffer.pBuffer[((int)grainIndex+2) % buffer.nBufferSize];
    int p1point = ((int)grainIndex-1) % buffer.nBufferSize;
    if (p1point < 0)
    {
        p1point += buffer.nBufferSize;
    }
    float yn_p1 = buffer.pBuffer[p1point];
    float fFracDelay = grainIndex - (int)grainIndex;
    
    float output = FourPointInterpolate(yn, yn_p1, yn_f1, yn_f2, fFracDelay);
    
    grainIndex = grainIndex + bufferSpeed;
    if (grainIndex > buffer.nBufferSize)
    {
        grainIndex -= buffer.nBufferSize;
    }
    
    return Window.doTukeyWindow(output, isBusy);
}

int Grain::returnIncrementer()
{
    return Window.incrementer;
}
