#include <iostream>
#include <cmath>
#include "portaudio.h"
#include "src/AudioNode.h"
#include "src/OscillatorNode.h"
#include "src/OutputNode.h"

struct AudioData {
    OscillatorNode* oscillator;
    OutputNode* output;
    int bufferSize;
    int numChannels;
};

int audioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    const unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    auto* out = static_cast<float*>(outputBuffer);
    auto data = static_cast<AudioData*>(userData);

    float leftBuffer[512];
    float rightBuffer[512];
    float* buffers[2] = {leftBuffer, rightBuffer};

    data->oscillator->process(nullptr, buffers, static_cast<int>(framesPerBuffer));
    data->output->setBuffer(out, static_cast<int>(framesPerBuffer));
    data->output->process(buffers, nullptr, static_cast<int>(framesPerBuffer));

    return paContinue;
}

int main() {

    auto* oscillator = new OscillatorNode(440.0f, 44100.0f);
    auto* output = new OutputNode(nullptr, 0);

    oscillator->prepare(44100.0, 512, 2);
    output->prepare(44100.0, 512, 2);


    AudioData data{oscillator, output, 512, 2};

    Pa_Initialize();

    PaStream* stream;

    if (Pa_GetDefaultOutputDevice() == paNoDevice) {
        std::cerr << "No output device found" << std::endl;
        return 1;
    }

    PaStreamParameters outputParams{
        Pa_GetDefaultOutputDevice(),
    data.numChannels,
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

    return 0;
}