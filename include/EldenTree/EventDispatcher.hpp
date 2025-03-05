#ifndef ELDENTREE_EVENT_DISPATCHER_HPP
#define ELDENTREE_EVENT_DISPATCHER_HPP

#include <functional>
#include <unordered_map>
#include <list>           // Use list instead of vector for efficient removal
#include <mutex>          // For std::unique_lock
#include <shared_mutex>   // For std::shared_timed_mutex (available in C++14)

namespace EldenTree {

    template<typename EventKey, typename EventData>
    class EventDispatcher {
    public:
        using Callback = std::function<void(const EventData&)>;
        using CallbackList = std::list<Callback>;

        // Subscribe a callback function to a given event key.
        void subscribe(const EventKey& key, Callback callback) {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            subscribers_[key].push_back(callback);
        }

        // Unsubscribe a specific callback function for a given event key.
        void unsubscribe(const EventKey& key, Callback callbackToRemove) {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            auto it = subscribers_.find(key);
            if (it != subscribers_.end()) {
                it->second.remove_if([&](const Callback& cb) {
                    return cb.template target<void(const EventData&)>() == callbackToRemove.template target<void(const EventData&)>();
                });
                if (it->second.empty()) {
                    subscribers_.erase(it);  // Remove the empty list
                }
            }
        }

        // Dispatch an event to all subscribers associated with the given key.
        void dispatch(const EventKey& key, const EventData& data) {
            std::shared_lock<std::shared_timed_mutex> lock(mutex_);
            auto it = subscribers_.find(key);
            if (it != subscribers_.end()) {
                for (const auto& callback : it->second) {
                    callback(data);  // Call directly to avoid unnecessary copying
                }
            }
        }

        // Dispatch an event to all subscribers across all event keys.
        void dispatch_all(const EventData& data) {
            std::shared_lock<std::shared_timed_mutex> lock(mutex_);
            for (auto &pair : subscribers_) {
                for (auto &callback : pair.second) {
                    callback(data);  // Call directly without extra copying
                }
            }
        }

    private:
        std::unordered_map<EventKey, CallbackList> subscribers_;
        mutable std::shared_timed_mutex mutex_;  // Use shared_timed_mutex (C++14 compatible)
    };

} // namespace EldenTree

#endif // ELDENTREE_EVENT_DISPATCHER_HPP
