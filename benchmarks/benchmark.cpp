#include <iostream>
#include <chrono>
#include "EldenTree/EventDispatcher.hpp"


// Define an enumeration for benchmark events.
enum class BenchmarkEvent {
    EventA,
    EventB
};

struct BenchmarkData {
    int value;
};

int main() {
    using namespace EldenTree;
    EventDispatcher<BenchmarkEvent, BenchmarkData> dispatcher;

    constexpr int iterations = 1000000;

    // Subscribe with empty callbacks to simulate minimal overhead.
    dispatcher.subscribe(BenchmarkEvent::EventA, [](const BenchmarkData&){});
    dispatcher.subscribe(BenchmarkEvent::EventB, [](const BenchmarkData&){});

    auto start = std::chrono::high_resolution_clock::now();

    // Dispatch events in a loop.
    for (int i = 0; i < iterations; ++i) {
        dispatcher.dispatch(BenchmarkEvent::EventA, BenchmarkData{i});
        dispatcher.dispatch(BenchmarkEvent::EventB, BenchmarkData{i});
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Benchmark: Dispatched " << (iterations * 2) 
              << " events in " << duration.count() << "ms" << std::endl;

    return 0;
}
