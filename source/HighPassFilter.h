//
// Created by David Richter on 1/7/25.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <vector>

class HighPassFilter {
public:
    HighPassFilter() = default;

    void process(juce::AudioBuffer<float>& buffer, double samplerate);

private:
    std::vector<float> mBuffer;

    bool mIsHighpass { true };
    float mCutoff { 1000.f };
};
