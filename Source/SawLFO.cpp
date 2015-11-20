/*
  ==============================================================================

    TriangleLFO.cpp
    Created: 6 Nov 2015 5:35:42pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "SawLFO.h"

SawLFO::SawLFO() : m_fPhase(0),
m_fFrequency(0),
m_fsampleRate(0)
{
    
}

SawLFO::~SawLFO(){}

void SawLFO::setPhase(float phase)
{
    m_fPhase = phase;
    if (m_fPhase < 0)
    {
        m_fPhase = 0;
    }
    if (m_fPhase > 1)
    {
        m_fPhase = m_fPhase - 1;
    }
}

void SawLFO::setSampleRate(float sampleRate)
{
    m_fsampleRate = sampleRate;
}

void SawLFO::setFrequency(float LFOFrequency)
{
    m_fFrequency = LFOFrequency;
}

float SawLFO::calcSawLFO(float centerValue, float modDepth)
{
    float LFOValue = centerValue + (modDepth*std::abs(2*m_fPhase));
    m_fPhase = m_fPhase + (m_fFrequency/m_fsampleRate);
    if (m_fPhase > 1)
    {
        m_fPhase = m_fPhase - 1;
    }
    return LFOValue;
}