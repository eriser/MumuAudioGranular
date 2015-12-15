/*
  ==============================================================================

    GranularBuffer.cpp
    Created: 19 Nov 2015 12:29:29pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "GranularBuffer.h"
#include <string.h>

GranularBuffer::GranularBuffer() : nWriteIndex(0),
                                   pBuffer(nullptr),
                                   nBufferSize(0)
                                    
{
    
}

GranularBuffer::~GranularBuffer()
{
    if(pBuffer)
        delete [] pBuffer;
    
}

void GranularBuffer::setBufferLength(float sampleRate, float seconds)
{
    nBufferSize = sampleRate * seconds;
}

int GranularBuffer::getBufferLength()
{
    return (int)nBufferSize;
}

void GranularBuffer::prepareToPlay()
{
    //delete if it exists
    if (pBuffer)
        delete [] pBuffer;
    //create new buffer
    pBuffer = new float[nBufferSize];
    if (pBuffer)
        memset(pBuffer, 0, nBufferSize*sizeof(float));
    nWriteIndex = 0;
}

void GranularBuffer::process(float input)
{
    pBuffer[nWriteIndex] = input;
    nWriteIndex++;
    if(nWriteIndex >= nBufferSize)
        nWriteIndex = 0;
}

