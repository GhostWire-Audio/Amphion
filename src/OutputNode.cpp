#include "OutputNode.h"

OutputNode::OutputNode(float* outputBuffer, int numFrames)
: outputBuffer(outputBuffer), numFrames(numFrames) {}

void OutputNode::prepare(double sr, int buf, int ch) {
    AudioNode::prepare(sr, buf, ch);
    (void)sampleRate;
    (void)bufferSize;
    this->numChannels = ch;
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
