#include "Engine.hpp"
#include "Player.hpp"
#include <memory>
#include <vector>
#include <string>

Player::Player(int aX, int aY): Entity(aX, aY)
{}

void Player::render(std::shared_ptr<std::vector<std::string>> screen)
{
    // "  ∧  "
    screen->at(x).at(this->y) = '^';
    if (this->x + 1 < BATTLEFIELD_HEIGHT) {
        // "<-|->"
        if (this->y - 2 >= 0) {
            screen->at(this->x + 1).at(this->y - 2) = '<';
        }

        if (this->y - 1 >= 0) {
            screen->at(this->x + 1).at(this->y - 1) = '-';
        }

        screen->at(this->x + 1).at(this->y) = '|';

        if (this->y + 1 < BATTLEFIELD_WIDTH) {
            screen->at(this->x + 1.).at(this->y + 1) = '-';
        }

        if (this->y + 2 < BATTLEFIELD_WIDTH) {
            screen->at(this->x + 1).at(this->y + 2) = '>';
        }

        if (this->x + 2 < BATTLEFIELD_HEIGHT) {
            // "  |  "
            screen->at(this->x + 2).at(this->y) = '|';
            if (this->x + 3 < BATTLEFIELD_HEIGHT) {
                // "  v  "
                screen->at(this->x + 3).at(this->y) = 'v';
            }
        }
    }
}

bool Player::isColliding(Entity *anEntity)
{
    if (((anEntity->getX() >= this->getX()) && (anEntity->getX() <= (this->getX() + 3))) && ((anEntity->getY() >= (this->getY() - 2)) && (anEntity->getY() <= (this->getY() + 2)))) {
        return true;
    }
    return false;
}

// std::string* Player::draw()
// {
//     std::string* plane = (std::string*) malloc(sizeof(std::string) * 4);
//     plane[0].append("  ∧  ");
//     plane[1].append("<-|->");
//     plane[2].append("  |  ");
//     plane[4].append("  v  ");

//     return plane;
// }
