#ifndef ELDENTREE_EVENT_DISPATCHER_HPP
#define ELDENTREE_EVENT_DISPATCHER_HPP

#include <functional>
#include <unordered_map>
#include <vector>
#include <mutex>

namespace EldenTree {

    // A templated event dispatcher that supports thread-safe subscription and event dispatching.
    // EventKey: identifier for event type (could be an enum, int, etc.)
    // EventData: data associated with an event.
    template<typename EventKey, typename EventData>
    class EventDispatcher {
    public:
        using Callback = std::function<void(const EventData&)>;

        // Subscribe a callback function to a given event key.
        void subscribe(const EventKey& key, Callback callback) {
            std::lock_guard<std::mutex> lock(mutex_);
            subscribers_[key].push_back(callback);
        }

        // Dispatch an event to all subscribers associated with the given key.
        void dispatch(const EventKey& key, const EventData& data) {
            std::vector<Callback> callbacks_copy;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                auto it = subscribers_.find(key);
                if (it != subscribers_.end()) {
                    callbacks_copy = it->second;
                }
            }
            for (auto &callback : callbacks_copy) {
                callback(data);
            }
        }

        // Dispatch an event to all subscribers across all event keys.
        void dispatch_all(const EventData& data) {
            std::vector<Callback> all_callbacks;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                for (auto &pair : subscribers_) {
                    all_callbacks.insert(all_callbacks.end(), pair.second.begin(), pair.second.end());
                }
            }
            for (auto &callback : all_callbacks) {
                callback(data);
            }
        }

    private:
        std::unordered_map<EventKey, std::vector<Callback>> subscribers_;
        mutable std::mutex mutex_;
    };

} // namespace EldenTree

#endif // ELDENTREE_EVENT_DISPATCHER_HPP
