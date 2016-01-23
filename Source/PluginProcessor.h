/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "GranularBuffer.h"
#include "GrainScheduler.h"
#include "Grain.h"
#include "EnvelopeGenerator.h"
//test


//==============================================================================
/**
*/
class MumuAudioGranularAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MumuAudioGranularAudioProcessor();
    ~MumuAudioGranularAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorParameter* Tab1_pitchKnobParam;
    AudioProcessorParameter* Tab1_densityKnobParam;
    AudioProcessorParameter* Tab1_grainSizeKnobParam;
    AudioProcessorParameter* Tab1_dryWayKnobParam;
    AudioProcessorParameter* Tab1_stretchSpeedKnobParam;
    
    AudioProcessorParameter* Tab1_stretchButtonParam;
    
    AudioProcessorParameter* currentTab;
    
//    //AudioSampleBuffer currentSampleBuffer;
//    std::atomic<bool> guiUpToDate;
//    std::shared_ptr<AudioSampleBuffer> sharedSampleBuffer;

    
private:
    //AudioSampleBuffer currentSampleBuffer;

    GranularBuffer m_gBufferL;
    GranularBuffer m_gBufferR;
    const float m_fMaxBufferLength = 10.0;
    
    GrainScheduler m_SchedulerL;
    GrainScheduler m_SchedulerR;
    
    const int m_nNumberGrains = 6;
    Grain* grainp_ArrayL;
    Grain* grainp_ArrayR;
    
    float m_fSampleRate;
    
    EnvelopeGenerator m_ADSR_Left;
    int m_ADSR_Left_Started;
    float stretchDeltaL;
    
    EnvelopeGenerator m_ADSR_Right;
    int m_ADSR_Right_Started;
    float stretchDeltaR;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MumuAudioGranularAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
