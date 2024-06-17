#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "Engine.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

void Engine::update()
{
    if (0 == this->frame % 60) {
        for (auto projectile = this->playerProjectiles.begin(); projectile != this->playerProjectiles.end(); ++projectile) {
            if ((projectile->get()->getX()) > 0) {
                projectile->get()->move();
            } else {
                projectile = this->playerProjectiles.erase(projectile);
            }
        }
        this->canShoot = true;

        this->frame = 0;
    }
    // A cada frame tem 1% de chance spawnar um novo inimigo
    if (1 == rand() % 100) {
        int y;
        do {
            y = rand() % BATTLEFIELD_WIDTH;
        } while (!this->tileInUse(0, y));
        this->enemies.push_back(std::unique_ptr<Enemy>(new Enemy(0, y)));
    }

    for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy) {
        // A cada frame cada inimigo tem 1% de chance de andar pra frente
        if (1 == rand() % 100) {
            if ((enemy->get()->getX() + 1) < BATTLEFIELD_HEIGHT) {
                enemy->get()->move(1, 0);
            } else {

                this->lives--;
                enemy = this->enemies.erase(enemy);
            }
        }
    }

    for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy) {
        for (auto projectile = this->playerProjectiles.begin(); projectile != this->playerProjectiles.end(); ++projectile) {
            if (enemy->get()->getX() == projectile->get()->getX() && enemy->get()->getY() == projectile->get()->getY()) {
                enemy = this->enemies.erase(enemy);
                projectile = this->playerProjectiles.erase(projectile);
                this->score++;
            }
        }
    }

    for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy) {
        if (this->player->isColliding(enemy->get())) {
            enemy = this->enemies.erase(enemy);
            this->lives--;
        }
    }

    if (this->lives <= 0) {
        this->gameOver = true;
    }

    this->frame++;
}

void Engine::render()
{
    printf("%s", "\033[2J\033[1;1H"); // Limpar terminal
    std::shared_ptr<std::vector<std::string>> screen = std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>);
    std::shared_ptr<std::vector<std::string>> mat = std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>);

    this->renderTopBorder(screen);

    // std::string helper;
    // helper.append("║");
    for (int i = 0; i < BATTLEFIELD_HEIGHT; i ++) {
        mat->push_back(std::string());
        mat->at(i).append(BATTLEFIELD_WIDTH, ' ');
    }

    this->player->render(mat);
    // Projectiles
    for (auto const& projectile: this->playerProjectiles) {
        projectile->render(mat);
    }

    // for (auto const& projectile: this->enemiesProjectiles) {
    //     projectile->render(mat);
    // }

    for (auto const& enemy: this->enemies) {
        enemy->render(mat);
    }

    std::string helper;
    for (int i = 0; i < BATTLEFIELD_HEIGHT; i++) {
        helper.clear();
        helper.append("║");
        helper.append(mat->at(i));
        helper.append("║");

        screen->push_back(helper);
    }

    this->renderBottomBorder(screen);
    this->renderStatus(screen);

    for (int i = 0; i < screen->size(); i++) {
        printf("%s\n", screen->at(i).c_str());
    }
}

bool Engine::tileInUse(int aX, int aY)
{
    for (auto const &enemy: enemies) {
        if (enemy->getX() == aX && enemy->getY() == aY) {
            return false;
        }
    }
    return true;
}

void Engine::start()
{
    while (!gameOver) {
        this->update();
        this->render();

        usleep((1000 * 1000) / 60);
    }
}

void Engine::addPlayer(Player *aPlayer)
{
    this->player = aPlayer;
}

void Engine::playerMove(int xVariation, int yVariation)
{
    if ((this->player->getX() + xVariation >= 0) && (this->player->getX() + xVariation < BATTLEFIELD_HEIGHT)) {
        this->player->move(xVariation, 0);
    }

    if ((this->player->getY() + yVariation >= 0) && (this->player->getY() + yVariation < BATTLEFIELD_WIDTH)) {
        this->player->move(0, yVariation);
    }
}

void Engine::playerShoot()
{
    if (this->canShoot) {
        this->playerProjectiles.push_back(std::unique_ptr<Projectile>(new Projectile(this->player->getX() - 1, this->player->getY(), -1, 0)));
        this->canShoot = false;
    }
}

void Engine::renderTopBorder(std::shared_ptr<std::vector<std::string>> screen)
{
    std::string helper;
    helper.append("╔");
    for (int j = 0; j < BATTLEFIELD_WIDTH; j++) {
        helper.append("═");
    }
    helper.append("╗");

    screen->push_back(helper);
}

void Engine::renderBottomBorder(std::shared_ptr<std::vector<std::string>> screen)
{
    std::string helper;
    helper.append("╚");
    for (int j = 0; j < BATTLEFIELD_WIDTH; j++) {
        helper.append("═");
    }
    helper.append("╝");

    screen->push_back(helper);
}

void Engine::renderStatus(std::shared_ptr<std::vector<std::string>> screen)
{
    std::string helper;
    helper.append("Vidas: " + std::to_string(this->lives) + "\n");
    helper.append("Pontuação: " + std::to_string(this->score) + "\n");
    screen->push_back(helper);
}
