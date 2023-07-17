/*
  ==============================================================================

    KAPLfo.cpp
    Created: 31 Dec 2022 4:21:11pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPLfo.h"
#include "JuceHeader.h"

KAPLfo::KAPLfo()
{
    Reset();
}

KAPLfo::~KAPLfo()
{

}

void KAPLfo::Reset()
{
    mPhase = 0.0f;
    juce::zeromem(mBuffer, sizeof(float) * maxBufferDelaySize);
}

void KAPLfo::SetSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPLfo::Process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = juce::jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);

    for (int i = 0; i < inNumSamples; i++)
    {
        mPhase = mPhase + (rate / mSampleRate);

        if (mPhase > 1.0f)
            mPhase = mPhase - 1.0f;

        const float lfoPosition = sinf(mPhase * k2PI) * inDepth;
        mBuffer[i] = lfoPosition;
    }
}

float* KAPLfo::GetBuffer()
{
    return mBuffer;
}