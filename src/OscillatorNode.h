#pragma once
#include "AudioNode.h"
#include <atomic>

/**
 * OscillatorNode -- Generates a continuous sine wave at a given frequency.
 * Writes identical samples to all output channels.
 */
class OscillatorNode : public AudioNode {
public:
    OscillatorNode(float frequency, float sampleRate);

    void prepare(double sr, int buf, int ch) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

    void setFrequency(float frequency);

private:
    float phase; // Current position in the sine cycle
    std::atomic<float> frequency;
};