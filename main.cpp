#include <iostream>
#include <cmath>
#include "portaudio.h"

struct AudioData {
    float phase;
    float frequency;
    float sampleRate;
};

int audioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    const unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    auto* out = static_cast<float *>(outputBuffer);

    auto data = static_cast<AudioData *>(userData);

    const float phaseIncrement = (2.0f * static_cast<float>(M_PI) * data->frequency) / data->sampleRate;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        out[i] = std::sin(data->phase);
        data->phase += phaseIncrement;
        if (data->phase >= 2.0f * M_PI) { data->phase -= 2.0f * M_PI; }
    }

    return paContinue;
}

int main() {
    Pa_Initialize();

    PaStream* stream;

    AudioData data{0.0f, 440.0f, 44100.0f};

    Pa_OpenDefaultStream(
        &stream,
        0,  // no input channels
        1,  // 1 output channel (mono)
        paFloat32,  // sample format
        data.sampleRate,  // sample rate
        256,    // frames per buffer
        audioCallback,
        &data
        );

    Pa_StartStream(stream);

    // keep program alive for 3 seconds
    Pa_Sleep(3000);

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}