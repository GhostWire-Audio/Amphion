#include "OscillatorNode.h"
#include <cmath>

OscillatorNode::OscillatorNode(float frequency, float sampleRate)
    : phase(0.0f), frequency(frequency), sampleRate(sampleRate), numChannels(0) {
}

void OscillatorNode::prepare(double newSampleRate, int bufferSize, int newNumChannels) {
    this->sampleRate = static_cast<float>(newSampleRate);
    this->numChannels = newNumChannels;
}

void OscillatorNode::process(float** inputs, float** outputs, int numSamples) {
    (void) inputs;
    const float phaseIncrement = (2.0f * static_cast<float>(M_PI) * frequency) / sampleRate;
    for (int i = 0; i < numSamples; i++) {
        // write the same sample to all channels
        for (int j = 0; j < numChannels; j++) {
            outputs[j][i] = std::sin(phase);
        }
        phase += phaseIncrement;
        // wrap phase to keep it between 0 and 2π
        if (phase > 2.0f * static_cast<float>(M_PI)) {
            phase -= 2.0f * static_cast<float>(M_PI);
        }
    }
}

void OscillatorNode::reset() {
    this->phase = 0.0f;
}