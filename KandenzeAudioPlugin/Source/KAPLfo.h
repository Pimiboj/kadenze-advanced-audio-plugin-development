/*
  ==============================================================================

    KAPLfo.h
    Created: 31 Dec 2022 4:21:11pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

class KAPLfo
{
public:
    KAPLfo();
    ~KAPLfo();

    void Reset();

    void SetSampleRate(double inSampleRate);

    void Process(float inRate, float inDepth, int inNumSamples);

    float* GetBuffer();

private:
    double mSampleRate;

    float mPhase;

    float mBuffer[maxBufferDelaySize];
};