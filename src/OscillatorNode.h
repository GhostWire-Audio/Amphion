#pragma once
#include "AudioNode.h"

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

private:
    float phase;        // current position in the sine cycle (0-2π)
    float frequency;    // pitch (Hz)
};