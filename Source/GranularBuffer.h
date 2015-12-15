/*
  ==============================================================================

    GranularBuffer.h
    Created: 19 Nov 2015 12:29:29pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef GRANULARBUFFER_H_INCLUDED
#define GRANULARBUFFER_H_INCLUDED

class GranularBuffer {
public:
    GranularBuffer();
    ~GranularBuffer();
    void setBufferLength(float sampleRate, float seconds);
    int getBufferLength();
    void prepareToPlay();
    void process(float input);
    
    int nWriteIndex;
    float* pBuffer;
    int nBufferSize;
    
private:
};



#endif  // GRANULARBUFFER_H_INCLUDED
