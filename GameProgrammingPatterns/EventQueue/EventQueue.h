#pragma once

#include <queue>
#include <memory>
#include "Event.h"

class EventQueue
{
public:
    void AddEvent(std::unique_ptr<Event> Event);
    void ProcessEvents();
    
private:
    std::queue<std::unique_ptr<Event>> Events;
};
