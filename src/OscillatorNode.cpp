#include "OscillatorNode.h"
#include <cmath>
#include <numbers>

OscillatorNode::OscillatorNode(float frequency, float sampleRate)
    : phase(0.0f), frequency(frequency) {
}

void OscillatorNode::prepare(double sr, int buf, int ch) {
    AudioNode::prepare(sr, buf, ch);
    sampleRate = sr;
    numChannels = ch;
}

void OscillatorNode::process(float** inputs, float** outputs, int numSamples) {
    (void) inputs;

    const double pi = std::numbers::pi;

    const float phaseIncrement = (2.0f * static_cast<float>(pi) * frequency) / static_cast<float>(sampleRate);
    for (int i = 0; i < numSamples; i++) {
        // write the same sample to all channels
        for (int j = 0; j < numChannels; j++) {
            outputs[j][i] = std::sin(phase);
        }
        phase += phaseIncrement;
        // wrap phase to keep it between 0 and 2π
        if (phase > 2.0f * static_cast<float>(pi)) {
            phase -= 2.0f * static_cast<float>(pi);
        }
    }
}

void OscillatorNode::reset() {
    this->phase = 0.0f;
}