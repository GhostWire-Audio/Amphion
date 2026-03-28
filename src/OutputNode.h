#pragma once
#include "AudioNode.h"

/**
 * OutputNode -- The final node in the graph.
 * Converts non-interleaved audio from the node system into
 * PortAudio's interleaved output buffer. Always sits at the
 * end of the signal chain.
 */
class OutputNode : public AudioNode {
public:
    OutputNode(float* outputBuffer, int numFrames);

    void prepare(double sr, int buf, int ch) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

    // Must be called each callback to update the PortAudio buffer pointer
    void setBuffer(float* newOutputBuffer, int newNumFrames);

private:
    float* outputBuffer;    // PortAudio's interleaved output buffer
    int numFrames;
};