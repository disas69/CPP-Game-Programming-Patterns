#pragma once

class PooledObject
{
public:
    PooledObject() = default;
    virtual ~PooledObject() = default;

    virtual void Initialize() {}
    virtual void Reset() {}
    virtual void Release() {}
};
