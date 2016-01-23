/*
  ==============================================================================

    GrainScheduler.cpp
    Created: 21 Nov 2015 2:41:18pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "GrainScheduler.h"
#include <iostream>

//==============================================================================
GrainScheduler::GrainScheduler(){
    m_fDelta = 0;
    m_nCounter = 0;
    m_nInteronsetInSample = 0;
}

//==============================================================================
GrainScheduler::~GrainScheduler(){

}

//==============================================================================
void GrainScheduler::setInteronset(float sampleRate, float seconds){
    m_nInteronsetInSample = sampleRate * seconds;
}

//==============================================================================
void GrainScheduler::setGrainSize(float sampleRate, float seconds){
    
}

//==============================================================================
void GrainScheduler::setDelta(float sampleRate, float seconds){
    
}

//==============================================================================
void GrainScheduler::prepareToPlay(){
    m_nCounter = 0;
}

//==============================================================================
void GrainScheduler::play(){
    m_nCounter++;
    if (m_nCounter > m_nInteronsetInSample)
    {
        m_nCounter = 0;
    }
}

//==============================================================================
bool GrainScheduler::bang(){
    if (m_nCounter >= m_nInteronsetInSample)
    {
        return true;
    }
    else
    {
        return false;
    }
}