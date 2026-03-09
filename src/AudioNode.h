#pragma once

/**
 * AudioNode -- Abstract base class for all nodes in Amphion.
 * Every node in teh graph inherits from this and must implement
 * prepare, process, and reset.
 */
class AudioNode {
public:
    virtual ~AudioNode() = default;

    // Called once before audio starts - sets sample rate, buffer size, and channel count
    virtual void prepare(double newSampleRate, int bufferSize, int numChannels) = 0;

    // Called every buffer tick - inputs/outputs are non-interleaved: [channel][sample]
    virtual void process(float** inputs, float** outputs, int numSamples) = 0;

    // Resets internal state back to 0
    virtual void reset() = 0;

};