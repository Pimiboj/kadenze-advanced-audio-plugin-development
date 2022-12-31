/*
  ==============================================================================

    KAPGain.h
    Created: 31 Dec 2022 4:21:18pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

class KAPGain
{
public:

    KAPGain();
    ~KAPGain();

    void process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender);
private:

};