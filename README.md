# Project Amphion

## What is Amphion?

**Project Amphion** is a real-time, node-based modular audio engine built from scratch in C++.
The goal is to let you build DSP (digital signal processing) systems by connecting nodes together.
Think of it like building a signal chain out of virtual modules, like oscillators, filters, or envelopes, where the connections between them define how sound flows and gets processed.

Now although I may eventually develop an Amphion-based DAW (digital audio workstation), this is not what that is, but rather an audio engine that could potentially be used to build audio software/plugins.

---

## Why?
Most audio software hides what's actually happening to your signal, whereas Amphion will expose it. The goal is to make signal flow visible and programmable, and to build something that can serve as a real testing and research sandbox for DSP work.
Also on a personal level, building it from scratch is a great way to actually understand how audio software works at a low level.

---

## Features (planned)
* Real-time audio graph engine with topological sorting
* Built-in nodes: oscillators, filters, envelopes, gain, meters, etc.
* Custom node API -- write and load your own nodes without touching engine internals
* Lock-free threading model for safe real-time audio processing
* Visual node editor (GUI)
* Save/load graph presets as JSON
* Per-node CPU profiler

---

## Tech stack
* **Langage:** C++17
* **Build System:** CMake
* **Audio I/O:** PortAudio
* **GUI:** Dear ImGUI

---

**Status**
This project is still in very early development. Currently working through core engine architecture

_Built by Jesse Whiting as a long-term systems engineering project. A GhostWire Audio project._
