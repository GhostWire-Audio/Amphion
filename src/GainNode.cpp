#include "GainNode.h"

GainNode::GainNode(float gain)
    : gain(gain) {}

void GainNode::prepare(double sr, int buf, int ch) {
    AudioNode::prepare(sr, buf, ch);

    (void)sampleRate;
    (void)bufferSize;
    this->numChannels = ch;
}

void GainNode::process(float** inputs, float** outputs, int numSamples) {
    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numChannels; j++) {
            outputs[j][i] = inputs[j][i] * gain;
        }
    }
}

void GainNode::reset() {

}