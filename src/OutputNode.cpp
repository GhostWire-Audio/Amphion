#include "OutputNode.h"

OutputNode::OutputNode(float* outputBuffer, int numFrames)
: outputBuffer(outputBuffer), numFrames(numFrames), numChannels(0) {}

void OutputNode::prepare(double newSampleRate, int bufferSize, int newNumChannels) {
    (void)newSampleRate;
    (void)bufferSize;
    this->numChannels = newNumChannels;
}

void OutputNode::process(float** inputs, float** outputs, int numSamples) {
    (void)outputs;
    // convert non-interleaved inputs[channel][sample] to interleaved PortAudio buffer
    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numChannels; j++) {
            outputBuffer[i * numChannels + j] = inputs[j][i];
        }
    }
}

void OutputNode::reset() {

}

void OutputNode::setBuffer(float* newOutputBuffer, int newNumFrames) {
    this->outputBuffer = newOutputBuffer;
    this->numFrames = newNumFrames;
}
