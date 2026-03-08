#include <iostream>

class AudioNode {
public:
    virtual void process() = 0;
};

class Oscillator : public AudioNode {
public:
    float frequency = 440.0f;

    void process() override {
        std::cout << "Oscillator running at " << frequency << " Hz" << std::endl;
    }
};

int main() {
    // Here I'm using AudioNode as a pointer, as in future renditions
    // I intend to process a list of nodes, and thus a list of nodes have to
    // be a single type.
    AudioNode* node = new Oscillator();
    node->process();
    return 0;
}