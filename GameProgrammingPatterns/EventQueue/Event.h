#pragma once

class Event
{
public:
    virtual ~Event() = default;
    virtual void Process() = 0;
};
