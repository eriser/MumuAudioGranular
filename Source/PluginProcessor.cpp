/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MumuAudioGranularAudioProcessor::MumuAudioGranularAudioProcessor() : grainp_ArrayL(nullptr),
                                                                     grainp_ArrayR(nullptr)
{
    m_gBufferL = GranularBuffer();
    m_gBufferR = GranularBuffer();
    
    m_SchedulerL = GrainScheduler();
    m_SchedulerR = GrainScheduler();
    
    //Set sliders connected variable
    addParameter(slider1Param = new AudioParameterFloat("slider1Param", "Slider1", 0.0, 1.0, 0.5));
    addParameter(slider2Param = new AudioParameterFloat("slider2Param", "Slider2", 0.0, 1.0, 0.5));
    addParameter(slider3Param = new AudioParameterFloat("slider3Param", "Slider3", 0.0, 1.0, 0.5));
    addParameter(slider4Param = new AudioParameterFloat("slider4Param", "Slider4", 0.0, 1.0, 0.5));
    addParameter(slider5Param = new AudioParameterFloat("slider5Param", "Slider5", 0.0, 1.0, 0.5));
    addParameter(currentTab = new AudioParameterFloat("currentTabParam", "Tab", 0, 2, 0));
    //Button Param
    addParameter(button1Param = new AudioParameterBool("button1Param", "Button1" , 0));
    
    m_ADSR_Left_Started = 0;
    m_ADSR_Right_Started = 0;
}

MumuAudioGranularAudioProcessor::~MumuAudioGranularAudioProcessor()
{
    if(grainp_ArrayL)
        delete [] grainp_ArrayL;
    
    if(grainp_ArrayR)
        delete [] grainp_ArrayR;
}

//==============================================================================
const String MumuAudioGranularAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String MumuAudioGranularAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String MumuAudioGranularAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool MumuAudioGranularAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool MumuAudioGranularAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool MumuAudioGranularAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MumuAudioGranularAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MumuAudioGranularAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double MumuAudioGranularAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MumuAudioGranularAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MumuAudioGranularAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MumuAudioGranularAudioProcessor::setCurrentProgram (int index)
{
}

const String MumuAudioGranularAudioProcessor::getProgramName (int index)
{
    return String();
}

void MumuAudioGranularAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MumuAudioGranularAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //std::cout << "prepare to play" << std::endl;
    m_fSampleRate = sampleRate;
    //Left Grains
    if (grainp_ArrayL)
        delete [] grainp_ArrayL;
    grainp_ArrayL = new Grain[m_nNumberGrains];
    //turn off all grains
    for (int i = 0; i < m_nNumberGrains; i++)
    {
        grainp_ArrayL[i].isBusy = 0;
    }
    //Right Grains
    if (grainp_ArrayR)
        delete [] grainp_ArrayR;
    grainp_ArrayR = new Grain[m_nNumberGrains];
    //turn off all grains
    for (int i = 0; i < m_nNumberGrains; i++)
    {
        grainp_ArrayR[i].isBusy = 0;
    }
    //set up grain buffers (audio data)
    m_gBufferL.setBufferLength(sampleRate, m_fMaxBufferLength);
    m_gBufferL.prepareToPlay();
    
    m_gBufferR.setBufferLength(sampleRate, m_fMaxBufferLength);
    m_gBufferR.prepareToPlay();
    //initialize Schedulers
    m_SchedulerL.prepareToPlay();
    m_SchedulerR.prepareToPlay();
    
    m_ADSR_Left.setSampleRate(m_fSampleRate);
    m_ADSR_Right.setSampleRate(m_fSampleRate);
    
}

void MumuAudioGranularAudioProcessor::releaseResources()
{
    
}

void MumuAudioGranularAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    //Clear Garbage Data
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    //Get Parameters
    float pitch = jmap(slider1Param->getValue(), 0.001f, 2.0f);
    float density = jmap(slider2Param->getValue(), 0.015f, 0.6f);
    float grainSize = jmap(slider3Param->getValue(), 0.01f, 0.5f);
    float dryWet = slider4Param->getValue();
    int buttonState = button1Param->getValue();
    float stretchSpeed = slider5Param->getValue();
    //Set Interonset Time
    m_SchedulerL.setInteronset(m_fSampleRate, density);
    m_SchedulerR.setInteronset(m_fSampleRate, density);
    //Parse Buffers And Process Samples
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        for ( int i = 0; i < buffer.getNumSamples(); i++ )
        {
            if (channel == 0)
            {
                m_gBufferL.process(channelData[i]);
                m_SchedulerL.play();
                //////Real Time Pitch Shift//////
                if (buttonState == 0)
                {
                    //Turn off our envelope on flag
                    m_ADSR_Left_Started = 0;
                    
                    if (m_SchedulerL.bang() == true)
                    {
                        for (int i = 0; i < m_nNumberGrains; i++)
                        {
                            if(grainp_ArrayL[i].isItBusy() == 0)
                            {
                                grainp_ArrayL[i].setWindowSize(m_fSampleRate, grainSize);
                                float delta = 0;
                                if (pitch > 1)
                                {
                                    delta = (pitch-1)*(grainSize*m_fSampleRate);
                                }
                                grainp_ArrayL[i].setDelta(m_fSampleRate, delta);
                                grainp_ArrayL[i].init(pitch, m_gBufferL);
                                grainp_ArrayL[i].isBusy = 1;
                                break;
                            }
                        }
                    }
                }
                //////Time Stretch//////
                if (buttonState == 1)
                {
                    if (m_ADSR_Left_Started != 1)
                    {
                        m_ADSR_Left.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
                        m_ADSR_Left_Started = 1;
                        stretchDeltaL = 0;
                    }
                    const float leftEnvValue = (m_ADSR_Left.nextSample()*4.5)*m_fSampleRate;
                    stretchDeltaL = fmod((stretchDeltaL + stretchSpeed), m_gBufferL.getBufferLength());
                    //std::cout << stretchDeltaL << std::endl;
                    //Do Time Stretching
                    if (m_SchedulerL.bang() == true)
                    {
                        for (int i = 0; i < m_nNumberGrains; i++)
                        {
                            if(grainp_ArrayL[i].isItBusy() == 0)
                            {
                                grainp_ArrayL[i].setWindowSize(m_fSampleRate, grainSize);
                                grainp_ArrayL[i].setDelta(m_fSampleRate, stretchDeltaL);
                                grainp_ArrayL[i].init(pitch, m_gBufferL);
                                grainp_ArrayL[i].isBusy = 1;
                                break;
                            }
                        }
                    }
                }
                /////Generate Output////
                float output = 0;
                for (int i = 0; i < m_nNumberGrains; i++)
                {
                    output += grainp_ArrayL[i].play(m_fSampleRate, m_gBufferL);
                }
                channelData[i] = (output * dryWet) + ((1 - dryWet) * channelData[i]);
            }
            if (channel == 1)
            {
                m_gBufferR.process(channelData[i]);
                m_SchedulerR.play();
                //////Real Time Pitch Shift//////
                if (buttonState == 0)
                {
                    m_ADSR_Right_Started = 0;
                    if (m_SchedulerR.bang() == true)
                    {
                        //std::cout << "bangR" << std::endl;
                        for (int i = 0; i < m_nNumberGrains; i++)
                        {
                            if(grainp_ArrayR[i].isItBusy() == 0)
                            {
                                grainp_ArrayR[i].setWindowSize(m_fSampleRate, grainSize);
                                float delta = 0;
                                if (pitch > 1)
                                {
                                    delta = (pitch-1)*(grainSize*m_fSampleRate);
                                }
                                grainp_ArrayR[i].setDelta(m_fSampleRate, delta);
                                grainp_ArrayR[i].init(pitch, m_gBufferR);
                                grainp_ArrayR[i].isBusy = 1;
                                break;
                            }
                        }
                    }
                }
                //////Time Stretch//////
                if (buttonState == 1)
                {
                    if (m_ADSR_Right_Started != 1)
                    {
                        m_ADSR_Right.enterStage(EnvelopeGenerator::ENVELOPE_STAGE_ATTACK);
                        m_ADSR_Right_Started = 1;
                        stretchDeltaR = 0;
                    }
                    const float rightEnvValue = (m_ADSR_Right.nextSample()*4.5) * m_fSampleRate;
                    stretchDeltaR = fmod((stretchDeltaR+stretchSpeed), m_gBufferR.getBufferLength());
                    //std::cout << rightEnvValue << std::endl;
                    // Do Time Stretching
                    if (m_SchedulerR.bang() == true)
                    {
                        //std::cout << "bangR" << std::endl;
                        for (int i = 0; i < m_nNumberGrains; i++)
                        {
                            if(grainp_ArrayR[i].isItBusy() == 0)
                            {
                                grainp_ArrayR[i].setWindowSize(m_fSampleRate, grainSize);
                                grainp_ArrayR[i].setDelta(m_fSampleRate, stretchDeltaR);
                                grainp_ArrayR[i].init(pitch, m_gBufferR);
                                grainp_ArrayR[i].isBusy = 1;
                                break;
                            }
                        }
                    }
                }
                /////Generate Output////
                float output = 0;
                for (int i = 0; i < m_nNumberGrains; i++)
                {
                    output += grainp_ArrayR[i].play(m_fSampleRate, m_gBufferR);
                }
                channelData[i] = (output * dryWet) + ((1 - dryWet) * channelData[i]);
            }
        } 
    }
//    std::shared_ptr<AudioSampleBuffer> newBuffer = std::make_shared<AudioSampleBuffer>(buffer);
//    std::atomic_store(&sharedSampleBuffer, newBuffer);
//    guiUpToDate.store(false);
//    std::cout << buttonState << std::endl;
}

//==============================================================================
bool MumuAudioGranularAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MumuAudioGranularAudioProcessor::createEditor()
{
    return new MumuAudioGranularAudioProcessorEditor (*this);
}

//==============================================================================
void MumuAudioGranularAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MumuAudioGranularAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MumuAudioGranularAudioProcessor();
}
