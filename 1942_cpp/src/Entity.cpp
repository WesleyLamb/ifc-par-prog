#include "Entity.hpp"
#include "Entity.hpp"

Entity::Entity(int aX, int aY)
{
    this->x = aX;
    this->y = aY;
}

int Entity::getX()
{
    return this->x;
}

int Entity::getY()
{
    return this->y;
}

void Entity::move(int xVariation, int yVariation)
{
    this->x += xVariation;
    this->y += yVariation;
}
