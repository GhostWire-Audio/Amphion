#pragma once

#include <vector>

/**
 * AudioNode -- Abstract base class for all nodes in Amphion.
 * Every node in teh graph inherits from this and must implement
 * prepare, process, and reset.
 */
class AudioNode {
public:
    virtual ~AudioNode() = default;

    // Called once before audio starts - sets sample rate, buffer size, and channel count
    virtual void prepare(double newSampleRate, int newBufferSize, int newNumChannels) {
        sampleRate = newSampleRate;
        bufferSize = newBufferSize;
        numChannels = newNumChannels;
        outputBuffers.resize(numChannels, std::vector<float>(bufferSize, 0.0f));
        outputBufferPtrs.resize(numChannels);
    }

    // Called every buffer tick - inputs/outputs are non-interleaved: [channel][sample]
    virtual void process(float** inputs, float** outputs, int numSamples) = 0;

    // Resets internal state back to 0
    virtual void reset() = 0;

    // ---

    float **getOutputBuffers() {
        for (int i = 0; i < numChannels; i++) {
            outputBufferPtrs[i] = outputBuffers[i].data();
        }
        return outputBufferPtrs.data();
    }

protected:
    double sampleRate = 0.0;
    int bufferSize = 0;
    int numChannels = 0;

    std::vector<std::vector<float>> outputBuffers;  // [channel][sample]
    std::vector<float*> outputBufferPtrs;
};