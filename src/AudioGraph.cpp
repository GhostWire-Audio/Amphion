#include "AudioGraph.h"

#include <map>
#include <queue>
#include <iostream>

void AudioGraph::addNode(AudioNode* node) {
    nodes.push_back(node);
    buildProcessingOrder();
}

void AudioGraph::connect(AudioNode* source, AudioNode* destination) {
    connections.push_back({source, destination});
    buildProcessingOrder();
}

void AudioGraph::buildProcessingOrder() {
    std::map<AudioNode*, int> inDegree;

    for (auto* node : nodes) {
        inDegree[node] = 0;
    }

    for (auto &c : connections) {
        inDegree[c.destination]++;
    }

    std::queue<AudioNode*> ready;
    for (auto* node : nodes) {
        if (inDegree[node] == 0) {
            ready.push(node);
        }
    }

    processes.clear();
    while (!ready.empty()) {
        AudioNode* node = ready.front();
        ready.pop();
        processes.push_back(node);

        for (auto& c : connections) {
            if (c.source == node) {
                inDegree[c.destination]--;
                if (inDegree[c.destination] ==0) {
                    ready.push(c.destination);
                }
            }
        }
    }

    if (processes.size() != nodes.size()) {
        std::cerr << "AudioGraph: cycle detected" << std::endl;
    }

    std::cout << "Processing order:" << std::endl;
    for (auto* node : processes)
        std::cout << "  " << typeid(*node).name() << std::endl;
}

void AudioGraph::prepare(double sampleRate, int bufferSize, int numChannels) {
    for (auto* node : nodes) {
        node->prepare(sampleRate, bufferSize, numChannels);
    }
}

void AudioGraph::process(int numSamples) {
    for (auto* node : processes) {
        std::vector<float*> inputPtrs;

        for (auto& c : connections) {
            if (c.destination == node) {
                float** srcBuffers = c.source->getOutputBuffers();
                // assuming stereo: push left and right
                inputPtrs.push_back(srcBuffers[0]);
                inputPtrs.push_back(srcBuffers[1]);
            }
        }

        float** inputs = inputPtrs.empty() ? nullptr : inputPtrs.data();
        node->process(inputs, node->getOutputBuffers(), numSamples);
    }
}