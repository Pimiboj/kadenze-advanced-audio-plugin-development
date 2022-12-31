/*
  ==============================================================================

    KAPGain.cpp
    Created: 31 Dec 2022 4:21:18pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPGain.h"

KAPGain::KAPGain()
{

}

KAPGain::~KAPGain()
{

}

void KAPGain::process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender)
{
    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        outAudio[i] = inAudio[i] * inGain;
    }
}