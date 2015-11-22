/*
  ==============================================================================

    GrainScheduler.h
    Created: 21 Nov 2015 2:41:18pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef GRAINSCHEDULER_H_INCLUDED
#define GRAINSCHEDULER_H_INCLUDED

class GrainScheduler
{
public:
    GrainScheduler();
    ~GrainScheduler();
    void setInteronset(float sampleRate, float seconds);
    void setGrainSize(float sampleRate, float seconds);
    void setDelta(float sampleRate, float seconds);
    void prepareToPlay();
    void play();
    bool bang();
private:
    int m_nInteronsetInSample;
    int m_nCounter;
    float m_fDelta;
};


#endif  // GRAINSCHEDULER_H_INCLUDED
