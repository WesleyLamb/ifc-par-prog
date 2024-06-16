#ifndef Engine_hpp
#define Engine_hpp
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <mutex>

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Projectile.hpp"

#define BATTLEFIELD_HEIGHT 20
#define BATTLEFIELD_WIDTH 10

class Engine {
    private:
        void renderTopBorder(std::shared_ptr<std::vector<std::string>> screen);
        void renderBottomBorder(std::shared_ptr<std::vector<std::string>> screen);
        void renderStatus(std::shared_ptr<std::vector<std::string>> screen);
    protected:
        std::list<std::unique_ptr<Enemy>> enemies;
        std::list<std::unique_ptr<Projectile>> playerProjectiles;
        // std::list<std::unique_ptr<Projectile>> enemiesProjectiles;

        Player* player;
        int lives = PLAYER_STARTING_LIVES;
        int score = 0;
        int frame = 0;
        bool canShoot = true;

        void update();
        void render();

        bool tileInUse(int aX, int aY);
    public:
        bool gameOver = false;

        Engine();
        ~Engine();

        void start();
        void addPlayer(Player* aPlayer);
        void playerMove(int xVariation, int yVariation);
        void playerShoot();
        // void addEnemy(Enemy* anEnemy);
};

#endif