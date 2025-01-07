// Event.h
#pragma once
#include <functional>
#include <vector>

// Event class template
template<typename... Args>
class Event {
public:
    using EventHandler = std::function<void(Args...)>;

    // Add a handler function
    void operator+=(const EventHandler& handler) {
        handlers.push_back(handler);
    }

    // Add a member function handler
    template <typename T>
    void Bind(void (T::* memberFunc)(Args...), T* instance) {
        handlers.push_back([=](Args... args) {
            (instance->*memberFunc)(args...);
            });
    }

    // Invoke the event
    void operator()(Args... args) const {
        for (const auto& handler : handlers) {
            handler(args...);
        }
    }

private:
    std::vector<EventHandler> handlers;
};