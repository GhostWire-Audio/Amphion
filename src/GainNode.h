#pragma once
#include "AudioNode.h"

class GainNode : public AudioNode {
public:
    GainNode(float gain);

    void prepare(double sr, int buf, int ch) override;
    void process(float** inputs, float** outputs, int numSamples) override;
    void reset() override;

private:
    float gain;
};
