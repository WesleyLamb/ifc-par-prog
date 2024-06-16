#ifndef Enemy_hpp
#define Enemy_hpp

#include "Entity.hpp"

class Enemy: public Entity {
    public:
        Enemy(int aX, int aY);
        void render(std::shared_ptr<std::vector<std::string>> screen);
};

#endif