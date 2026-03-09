//
// Created by Jesse on 3/9/2026.
//

#ifndef AMPHION_AUDIONODE_H
#define AMPHION_AUDIONODE_H

#pragma once
class AudioNode {
public:
    virtual ~AudioNode() = default;

    virtual void prepare(double sampleRate, int bufferSize) = 0;
    virtual void process(float** inputs, float** outputs, int numSamples) = 0;
    virtual void reset() = 0;

};

#endif //AMPHION_AUDIONODE_H