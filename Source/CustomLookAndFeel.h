/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 2 Dec 2014 10:51:33am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V3
{
  
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();
    
    void drawRotarySlider (Graphics & g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, Slider & slider);
    
private:
    
};




#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
