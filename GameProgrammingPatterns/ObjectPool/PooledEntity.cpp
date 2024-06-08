#include "PooledEntity.h"
#include <iostream>

void PooledEntity::Initialize()
{
    std::cout << "PooledEntity::Initialize()" << std::endl;
}

void PooledEntity::Reset()
{
    PooledObject::Reset();
}

void PooledEntity::Release()
{
    PooledObject::Release();
}

void PooledEntity::SetPosition(float X, float Y)
{
    this->X = X;
    this->Y = Y;
}

float PooledEntity::GetXPosition()
{
    return X;
}

float PooledEntity::GetYPosition()
{
    return Y;
}

PooledEntity::~PooledEntity()
{
    std::cout << "PooledEntity::~PooledEntity()" << std::endl;
}