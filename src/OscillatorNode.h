#pragma once
#include "AudioNode.h"

/**
 * OscillatorNode -- Generates a continuous sine wave at a given frequency.
 * Writes identical samples to all output channels.
 */
class OscillatorNode : public AudioNode {
public:
    OscillatorNode(float frequency, float sampleRate);

    void prepare(double newSampleRate, int bufferSize, int newNumChannels) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

private:
    float phase;        // current position in the sine cycle (0-2π)
    float frequency;    // pitch (Hz)
    float sampleRate;   // samples per second
    int numChannels;    // number of output channels
};