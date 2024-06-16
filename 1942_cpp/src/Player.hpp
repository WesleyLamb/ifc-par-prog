#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"
#include <memory>
#include <vector>
#include <string>

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 4
#define PLAYER_STARTING_LIVES 3

class Player: public Entity {
    public:
        Player(int aX, int aY);
        void render(std::shared_ptr<std::vector<std::string>> screen);
        bool isColliding(Entity* anEntity);
};

#endif