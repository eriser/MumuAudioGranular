/*
  ==============================================================================

    TukeyWindow.cpp
    Created: 16 Oct 2015 9:55:30pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "TukeyWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"

TukeyWindow::TukeyWindow():
PI(3.14159265359),
incrementer(0),
timeInSamples(0),
multiplier(0)
{
}
TukeyWindow::~TukeyWindow(){}

void TukeyWindow::setWindowLength(int sampleRate, float seconds)
{
    timeInSamples = sampleRate * seconds;
}

float TukeyWindow::doTukeyWindow(float input, int& logicSwitch)
{
    if (logicSwitch == 1)
    {
        if (incrementer <= (timeInSamples/2))
        {
            multiplier = 0.5 * (1+cos(((2*PI)/timeInSamples)*(incrementer-(timeInSamples/2))));
            incrementer++;
        }
        if (incrementer > (timeInSamples/2))
        {
            multiplier = 0.5 * (1+cos(((2*PI)/timeInSamples)*((incrementer - 1)+(timeInSamples/2))));
            incrementer++;
        }
        if (incrementer == timeInSamples)
        {
            logicSwitch = 0;
            incrementer = 0;
        }
        //std::cout << multiplier << std::endl;
        return input * multiplier;
    }
    if (logicSwitch == 0)
    {
        return input * 0;
    }
    else
    {
        return input * 0;
    }
    
}