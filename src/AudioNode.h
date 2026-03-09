//
// Created by Jesse on 3/9/2026.
//
#pragma once
class AudioNode {
public:
    virtual ~AudioNode() = default;

    virtual void prepare(double newSampleRate, int bufferSize, int numChannels) = 0;
    virtual void process(float** inputs, float** outputs, int numSamples) = 0;
    virtual void reset() = 0;

};