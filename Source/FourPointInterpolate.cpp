/*
  ==============================================================================

    FourPointInterpolate.cpp
    Created: 4 Oct 2015 10:42:03pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "FourPointInterpolate.h"

float FourPointInterpolate(float t0, float t_minus1, float t_1, float t_2, float fractional)
{
    float numeralA = (t_1 - t_minus1) * 0.5;
    float numeralB = (t_2 - t0) * 0.5;
    float numeralC = (t0 - t_1);
    
    float numeralD = numeralC + numeralA;
    float numeralE = numeralD + numeralB;
    float numeralF = numeralE + numeralC;
    float numeralG = numeralD + numeralF;
    float numeralH = numeralF * fractional;
    float numeralI = numeralH - numeralG;
    float numeralJ = numeralI * fractional;
    float numeralK = numeralJ + numeralA;
    float numeralL = fractional * numeralK;
    
    return t0 + numeralL;
}
