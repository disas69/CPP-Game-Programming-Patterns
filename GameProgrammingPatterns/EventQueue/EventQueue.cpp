#include <iostream>
#include "EventQueue.h"

void EventQueue::AddEvent(std::unique_ptr<Event> Event)
{
    if (Event != nullptr)
    {
        Events.push(std::move(Event));
    }
}

void EventQueue::ProcessEvents()
{
    while (!Events.empty())
    {
        std::unique_ptr<Event> Event = std::move(Events.front());
        Events.pop();

        if (Event != nullptr)
        {
            try
            {
                Event->Process();
            }
            catch (const std::exception& Exception)
            {
                std::cerr << "Exception: " << Exception.what() << std::endl;
            }
        }
    }
}