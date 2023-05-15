/*
  ==============================================================================

    KAPAudioHelpers.h
    Created: 31 Dec 2022 4:20:37pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

inline float kap_linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}