/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 24 Nov 2015 11:24:51am
    Author:  Jacob Penn

  ==============================================================================
*/

#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator() :    mCurrentStage(ENVELOPE_STAGE_OFF),
                                            mSampleRate(44100.0),
                                            mMultiplier(1),
                                            mCurrentLevel(mMinimumLevel),
                                            mCurrentSampleIndex(0),
                                            mNextStageSampleIndex(0)
{
    //The Envelope Stages are in Time (seconds), Except the sustain which is the volume of the sustain of the synth
    stageValue[ENVELOPE_STAGE_OFF] = 0.0;
    stageValue[ENVELOPE_STAGE_ATTACK] = 4.0;
    stageValue[ENVELOPE_STAGE_DECAY] = .01;
    stageValue[ENVELOPE_STAGE_SUSTAIN] = 1.0;
    stageValue[ENVELOPE_STAGE_RELEASE] = 1.0;
}

EnvelopeGenerator::~EnvelopeGenerator(){
    
}

void EnvelopeGenerator::enterStage(EnvelopeStage newStage){
    //Enter new stage and make sure to reset current sample index so we can start calculating current stage
    mCurrentStage = newStage;
    mCurrentSampleIndex = 0;
    //If we're in Attack Decay or Release, Calculate how long until the next stage, otherwise mNextStageSampleIndex is 0
    if (mCurrentStage == ENVELOPE_STAGE_OFF || mCurrentStage == ENVELOPE_STAGE_SUSTAIN){
        mNextStageSampleIndex = 0;
    } else {
        mNextStageSampleIndex = stageValue[mCurrentStage] * mSampleRate;
    }
    switch (mCurrentStage) {
        case ENVELOPE_STAGE_OFF:
            mCurrentLevel = 0.0;
            mMultiplier = 1.0;
            break;
        case ENVELOPE_STAGE_ATTACK:
            mCurrentLevel = mMinimumLevel;
            calculateMultiplier(mCurrentLevel, 1.0, mNextStageSampleIndex);
            break;
        case ENVELOPE_STAGE_DECAY:
            mCurrentLevel = 1.0;
            calculateMultiplier(mCurrentLevel, fmax(stageValue[ENVELOPE_STAGE_SUSTAIN],mMinimumLevel), mNextStageSampleIndex);
            break;
        case ENVELOPE_STAGE_SUSTAIN:
            mCurrentLevel = stageValue[ENVELOPE_STAGE_SUSTAIN];
            mMultiplier = 1.0;
            break;
        case ENVELOPE_STAGE_RELEASE:
            calculateMultiplier(mCurrentLevel, mMinimumLevel, mNextStageSampleIndex);
            break;
        default: break;
    }
}

double EnvelopeGenerator::nextSample(){
    // If we're in Attack, Decay, Release, if mCurrentSampleIndex, has reached the next stage, then get the next stage and enter it.
    // Go to off from release
    if (mCurrentStage != ENVELOPE_STAGE_OFF && mCurrentStage != ENVELOPE_STAGE_SUSTAIN){
        if (mCurrentSampleIndex == mNextStageSampleIndex){
            EnvelopeStage newStage = static_cast<EnvelopeStage>((mCurrentStage+1)%kNumEnvelopeStages);
            enterStage(newStage);
        }
        mCurrentLevel *= mMultiplier;
        mCurrentSampleIndex++;
    }
    return mCurrentLevel;
}

void EnvelopeGenerator::calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples){
    mMultiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

