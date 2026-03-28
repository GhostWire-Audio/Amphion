#pragma once
#include "AudioNode.h"
#include <vector>

struct Connection {
    AudioNode* source;
    AudioNode* destination;
};

class AudioGraph {
public:
    void addNode(AudioNode* node);
    void connect(AudioNode* source, AudioNode* destination);
    void prepare(double sampleRate, int bufferSize, int numChannels);
    void process(int numSamples);

private:
    std::vector<AudioNode*> nodes;
    std::vector<Connection> connections;
    std::vector<AudioNode*> processes;

    void buildProcessingOrder();
};