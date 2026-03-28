#include <iostream>
#include "portaudio.h"
#include "src/OscillatorNode.h"
#include "src/OutputNode.h"
#include "src/GainNode.h"
#include "src/AudioGraph.h"

/**
 *  main.cpp is, as typical, the "entry point" for Amphion.
 *  It sets up the node graph, initializes PortAudio, and runs the audio stream.
 *  Graph traversal and buffer routing are handled automatically by AudioGraph.
 */

struct AudioData {
    AudioGraph* graph;
    OutputNode* output;
};

int audioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    const unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    auto* out = static_cast<float*>(outputBuffer);
    auto* data = static_cast<AudioData*>(userData);

    data->output->setBuffer(out, static_cast<int>(framesPerBuffer));
    data->graph->process(static_cast<int>(framesPerBuffer));

    return paContinue;
}

int main() {
    auto* oscillator = new OscillatorNode(440.0f, 44100.0f);
    auto* gain = new GainNode(1.0f);
    auto* output = new OutputNode(nullptr, 0);

    auto* graph = new AudioGraph();
    graph->addNode(oscillator);
    graph->addNode(gain);
    graph->addNode(output);

    graph->connect(oscillator, gain);
    graph->connect(gain, output);

    graph->prepare(44100.0, 512, 2);

    AudioData data{graph, output};

    Pa_Initialize();

    PaStream* stream;

    if (Pa_GetDefaultOutputDevice() == paNoDevice) {
        std::cerr << "No output devices found" << std::endl;
        return 1;
    }

    PaStreamParameters outputParams{
    Pa_GetDefaultOutputDevice(),
    2,
    paFloat32,
    Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency,
    nullptr};

    PaError err = Pa_OpenStream(&stream, nullptr, &outputParams,
        44100.0, 512, paClipOff, audioCallback, &data);
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    Pa_Sleep(3000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    delete oscillator;
    delete output;
    delete gain;
    delete graph;
}
