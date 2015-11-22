/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 2 Dec 2014 10:51:33am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel(){
    setColour(Slider::rotarySliderFillColourId, Colours::darkgrey);
    setColour(Slider::rotarySliderOutlineColourId, Colours::black);
}

CustomLookAndFeel::~CustomLookAndFeel(){
    
}

// The version uses an image generated from knobman
// Based on https://github.com/audioplastic/Juce-look-and-feel-examples and JUCE Forum
void CustomLookAndFeel::drawRotarySlider (Graphics & g, int x, int y, int width, int height,  float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider & slider)
{
    // Load the image from binary data efficiently
    Image myStrip = ImageCache::getFromMemory(BinaryData::BlackKnob_png, BinaryData::BlackKnob_pngSize);
    
    //(val-min) / (max-min)
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum()-slider.getMinimum());
    
    const int numFrames = myStrip.getHeight() / myStrip.getWidth();
    const int frameIdx = (int)ceil(fractRotation * (numFrames-1.0));
    
    const float radius = jmin(width*0.5, height * 0.5);
    const float centerX = x+width * 0.5;
    const float centerY = y+height * 0.5;
    const float rx = centerX - radius;
    const float ry = centerY - radius;
    
    g.drawImage(myStrip, rx, ry, 2*radius, 2*radius, 0, frameIdx*myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth());
    
}



//This version draws a vector image using JUCE::Path
/*void CustomLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    
    // If the component is enabled. use Component::findColour and the ColourID to set it's colour
    // isMouseOver ? 1.0f : 0.7f is equivalent to say, if isMouseOver (which is a bool) is true, set alpha to 1.0, otherwise set it to 0.7
    if (slider.isEnabled())
        g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
    else
        g.setColour (Colour (0x80808080));
    
    {
        // Create Path Object
        Path filledArc;
        filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
        g.fillPath (filledArc);
    }
    
    {
        const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
        Path outlineArc;
        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
        g.strokePath (outlineArc, PathStrokeType (lineThickness));
    }
}*/

// Another path based version using affine transformation to rotate
/*void CustomLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    const float diameter = jmin (width, height) - 4.0f;
    //cos(pi/4) or cos(45degrees) = radius so this is radius * length we want
    const float radius = (diameter / 2.0f) * std::cos (float_Pi / 4.0f);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    
    // Again, shorthand syntax is used here to apply a color, but only if the slider is enabled
    // if slider.isEnabled() then find the color, taking into account if the mouse is over/hovering, and set baseColour to the color
    const Colour baseColour (slider.isEnabled() ? slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 0.8f : 1.0f)
                             : Colour (0x80808080));
    
    Rectangle<float> r (rx, ry, rw, rw);
    
    // Create the transformation (rotation)
    AffineTransform t (AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
    
    //Apply the transformation (rotation)
    float x1 = r.getTopLeft().getX(), y1 = r.getTopLeft().getY(), x2 = r.getBottomLeft().getX(), y2 = r.getBottomLeft().getY();
    t.transformPoints (x1, y1, x2, y2);
    
    g.setGradientFill (ColourGradient (baseColour, x1, y1,
                                       baseColour.darker (0.1f), x2, y2,
                                       false));
    
    Path knob;
    knob.addRectangle (r);
    g.fillPath (knob, t);
    
    Path needle;
    Rectangle<float> r2 (r * 0.1f);
    needle.addRectangle (r2.withPosition (Point<float> (r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));
    
    g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
    g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
}*/