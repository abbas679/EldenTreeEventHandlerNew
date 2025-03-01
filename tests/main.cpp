#include <iostream>
#include "EldenTree/EventDispatcher.hpp"

// Define an enumeration for different god events.
enum class GodEvent {
    Lightning,
    Fire,
    Water,
    Earth
};

// Event data structure containing a simple message.
struct EventData {
    std::string message;
};

int main() {
    using namespace EldenTree;
    EventDispatcher<GodEvent, EventData> dispatcher;

    // Subscribe callbacks for specific events.
    dispatcher.subscribe(GodEvent::Lightning, [](const EventData& data) {
        std::cout << "[Lightning] " << data.message << std::endl;
    });

    dispatcher.subscribe(GodEvent::Fire, [](const EventData& data) {
        std::cout << "[Fire] " << data.message << std::endl;
    });

    // Dispatch events for individual gods.
    dispatcher.dispatch(GodEvent::Lightning, EventData{"Thunder strikes!"});
    dispatcher.dispatch(GodEvent::Fire, EventData{"Flames engulf the horizon!"});

    // Dispatch a universal event to all subscribers.
    std::cout << "Dispatching to all gods:" << std::endl;
    dispatcher.dispatch_all(EventData{"The universal event unfolds."});

    return 0;
}
