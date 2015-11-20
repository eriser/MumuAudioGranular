/*
  ==============================================================================

    TriangleLFO.h
    Created: 6 Nov 2015 5:35:42pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef SAWLFO_H_INCLUDED
#define SAWLFO_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SawLFO
{
public:
    SawLFO();
    ~SawLFO();
    void setPhase(float phase);
    void setFrequency(float LFOFrequency);
    void setSampleRate(float sampleRate);
    float calcSawLFO(float centerValue, float modDepth);
private:
    float m_fPhase;
    float m_fFrequency;
    float m_fsampleRate;
};



#endif  // TRIANGLELFO_H_INCLUDED
