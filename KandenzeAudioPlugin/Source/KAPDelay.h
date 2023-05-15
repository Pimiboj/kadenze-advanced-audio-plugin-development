/*
  ==============================================================================

    KAPDelay.h
    Created: 31 Dec 2022 4:21:28pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

const int maxBufferDelaySize = 192000;

class KAPDelay
{
public:
    KAPDelay();
    ~KAPDelay();

    void SetSampleRate(double inSampleRate);
    void Reset();
    void Process(float* inAudio, float inTime, float inFeedback, float inWetDry, float* outAudio, int inNumSamplesToRender);

private:
    /* Circular Buffer components */
    double getInterpolatedSample(float inDelayTimeInSamples);

    double mSampleRate;
    double mBuffer[maxBufferDelaySize];
    double mFeedbackSample;

    int mDelayIndex;
};