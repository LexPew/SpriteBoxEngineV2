#pragma once

class Action
{
private:
    std::function<void()> callback; // Function to call when the action is invoked

public:
    // Constructors
    Action() = default; // Default constructor
    Action(std::function<void()> func) : callback(func) {}

    // Invoke the callback
    void Invoke()
    {
        if (callback)
        {
            callback();
        }
    }

    // Assign a new callback
    void SetCallback(std::function<void()> func)
    {
        callback = func;
    }

    // Clear the callback
    void Clear()
    {
        callback = nullptr;
    }

    // Check if the action has a valid callback
    bool IsValid() const
    {
        return static_cast<bool>(callback);
    }
};