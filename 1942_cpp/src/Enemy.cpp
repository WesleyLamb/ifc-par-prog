#include "Enemy.hpp"

Enemy::Enemy(int aX, int aY): Entity(aX, aY) {}

void Enemy::render(std::shared_ptr<std::vector<std::string>> screen)
{
    screen->at(this->x).at(this->y) = 'v';
}