#pragma once

#include "AudioNode.h"

class OutputNode : public AudioNode {
public:
    OutputNode(float* outputBuffer, int numFrames);

    void prepare(double newSampleRate, int bufferSize, int newNumChannels) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

    void setBuffer(float* newOutputBuffer, int newNumFrames);

private:
    float* outputBuffer;
    int numFrames;
    int numChannels;
};