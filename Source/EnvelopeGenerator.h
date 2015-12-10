/*
  ==============================================================================

    EnvelopeGenerator.h
    Created: 24 Nov 2015 11:24:51am
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef ENVELOPEGENERATOR_H_INCLUDED
#define ENVELOPEGENERATOR_H_INCLUDED
#include <math.h>

class EnvelopeGenerator{
    
public:
    EnvelopeGenerator();
    ~EnvelopeGenerator();
    
    enum EnvelopeStage{             //Enum To Define All Of The Stages of The Envelope
        ENVELOPE_STAGE_OFF = 0,
        ENVELOPE_STAGE_ATTACK,
        ENVELOPE_STAGE_DECAY,
        ENVELOPE_STAGE_SUSTAIN,
        ENVELOPE_STAGE_RELEASE,
        kNumEnvelopeStages
    };
    
    void enterStage(EnvelopeStage newStage);
    
    double nextSample();            //Gets The Next Sample of Envelope
    void setSampleRate(double sampleRate){mSampleRate = sampleRate;};
    EnvelopeStage getCurrentStage(){return mCurrentStage;};
    
    double stageValue[kNumEnvelopeStages];
    
    
private:
    EnvelopeStage mCurrentStage;    //Stores Current Stage of Envelope
    double mSampleRate;             //Current SampleRate
    double mMultiplier;             //Envelope Scaler Value
    const double mMinimumLevel = 0.0001;    //Needed to make sure math works, amplitude cannot be zero
    double mCurrentLevel;           //the current amp level
    
    unsigned long long mCurrentSampleIndex;
    unsigned long long mNextStageSampleIndex;
    //Calculate Exponential transition over time <from musicDSP>
    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
};



#endif  // ENVELOPEGENERATOR_H_INCLUDED
