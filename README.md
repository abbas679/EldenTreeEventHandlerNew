# EldenTree Event Handler

This project reimplements the Elden Tree’s event handler in C++ to ensure speed and reliability for handling events from the gods.

## Features

- **Modern C++:** Uses C++14 for modern language features.
- **Templated Event Dispatcher:** Provides a flexible, thread-safe event handling mechanism.
- **Benchmarking:** Includes a benchmark tool to measure dispatch performance.
- **Cross-Platform:** Designed to work on Windows 11 with VS Code, MSYS2, MinGW, and CMake.

## Project Structure

- **include/EldenTree/EventDispatcher.hpp:** Header-only library for event dispatching.
- **tests/main.cpp:** Demonstrates basic usage of the event dispatcher.
- **benchmarks/benchmark.cpp:** Benchmarking tool for performance evaluation.
- **CMakeLists.txt:** Build configuration for the project.

## Building the Project

Ensure you have CMake installed. From the project root, run:

```bash
mkdir build
cd build
cmake ..
cmake --build .
