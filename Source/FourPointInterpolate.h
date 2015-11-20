/*
  ==============================================================================

    FourPointInterpolate.h
    Created: 4 Oct 2015 10:42:03pm
    Author:  Jacob Penn
    this is a four point interpolate function for use in conjunction with the 
    four point delay

  ==============================================================================
*/

#ifndef FOURPOINTINTERPOLATE_H_INCLUDED
#define FOURPOINTINTERPOLATE_H_INCLUDED

float FourPointInterpolate(float t0, float t_minus1, float t_1, float t_2, float fractional);

#endif  // FOURPOINTINTERPOLATE_H_INCLUDED
