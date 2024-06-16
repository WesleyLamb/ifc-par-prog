#ifndef Projectile_hpp
#define Projectile_hpp

#include "Entity.hpp"

class Projectile: public Entity {
    protected:
        int xVariation;
        int yVariation;
    public:
        Projectile(int aX, int aY, int aXVariation, int aYVariation);
        void render(std::shared_ptr<std::vector<std::string>> screen);
        void move();

};

#endif