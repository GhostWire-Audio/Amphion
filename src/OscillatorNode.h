#pragma once
#include "AudioNode.h"

class OscillatorNode : public AudioNode {
public:
    OscillatorNode(float frequency, float sampleRate);

    void prepare(double newSampleRate, int bufferSize, int newNumChannels) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

private:
    float phase;
    float frequency;
    float sampleRate;
    int numChannels;
};