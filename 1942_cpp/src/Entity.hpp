#ifndef Entity_hpp
#define Entity_hpp
#include <memory>
#include <vector>
#include <string>

class Entity {
    protected:
        int x;
        int y;
    public:
        Entity(int aX, int aY);
        virtual void render(std::shared_ptr<std::vector<std::string>> screen) = 0;

        int getX();
        int getY();
        void move(int xVariation, int yVariation);
};

#endif