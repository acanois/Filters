//
// Created by David Richter on 1/7/25.
//

#include "HighPassFilter.h"

void HighPassFilter::process(juce::AudioBuffer<float>& buffer, double samplerate) {
    // Resets the size of the buffer and sets all values to 0.f
    mBuffer.resize(static_cast<unsigned long>(buffer.getNumChannels()), 0.f);

    const auto pi = juce::MathConstants<float>::pi;
    const auto sign = mIsHighpass ? -1.f : 1.f;

    // Calculating allpass coefficient
    const auto tan = std::tan(pi * mCutoff / samplerate);
    const auto a1 = (tan - 1.f) / (tan + 1.f);

    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto channelWritePtr = buffer.getWritePointer(channel);

        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample) {
            const auto inputSample = channelWritePtr[sample];

            // allpass filter
            const auto apfSample = a1 * inputSample + mBuffer[channel];
            mBuffer[channel] = inputSample - a1 * apfSample;

            // hpf or lpf applied - scaled by 0.5 to stay in [-1, 1]
            const auto outputSample = 0.5f * (inputSample + sign * apfSample);

            // assign to output
            channelWritePtr[sample] = outputSample;
        }
    }
}
