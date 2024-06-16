#include "Projectile.hpp"

Projectile::Projectile(int aX, int aY, int aXVariation, int aYVariation): Entity(aX, aY)
{
    this->xVariation = aXVariation;
    this->yVariation = aYVariation;
}

void Projectile::render(std::shared_ptr<std::vector<std::string>> screen)
{
    screen->at(this->x).at(this->y) = '|';
}

void Projectile::move()
{
    this->x += xVariation;
    this->y += yVariation;
}
