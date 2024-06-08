#pragma once

#include "PooledObject.h"

class PooledEntity : public PooledObject
{
public:
    PooledEntity() = default;
    virtual ~PooledEntity() override;

    virtual void Initialize() override;
    virtual void Reset() override;
    virtual void Release() override;

    void SetPosition(float X, float Y);
    float GetXPosition();
    float GetYPosition();

private:
    float X;
    float Y;
};