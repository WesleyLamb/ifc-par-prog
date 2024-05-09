#include "Battlefield.h"
#include "EnemyList.h"
#include "Plane.h"
#include "ProjectileList.h"
#include "Projectile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void drawScreenTop(char*, Battlefield*);
void drawGameBoard(char*, Battlefield*, Plane*, EnemyList*, ProjectileList*, ProjectileList*);
void drawGameBoardBottom(char*, Battlefield*);
// void drawGameInfo(char*, Battlefield*, Plane*, EnemyList*);
void renderEnemies(char*, EnemyList*);
void renderPlane(char***, Plane*, int, int);
void renderProjectiles(char***, ProjectileList*, int, int);
void zeroFill(char*);
void appendStr(char*, char*);
void moveEnemies(Battlefield*, EnemyList*, Plane*);
void moveProjectiles(Battlefield*, ProjectileList*);
void hitEnemies(ProjectileList*, EnemyList*, Plane*);
void hitPlayerWithEnemy(EnemyList*, Plane*);
void hitPlayer(ProjectileList*, Plane*);
void deleteEnemiesOutOfBounds(Battlefield*, EnemyList*, Plane*);
void deleteProjectilesOutOfBounds(Battlefield*, ProjectileList*);
bool projectileAndPlaneAreColliding(Projectile*, Plane*);
bool enemyAndPlaneAreColliding(Enemy*, Plane*);
bool projectileAndEnemyAreColliding(Projectile*, Enemy*);
void spawnNewEnemies(Battlefield*, EnemyList*);

Battlefield *createNewBattlefield()
{
    Battlefield*  battlefield = malloc(sizeof(Battlefield));
    battlefield->height = BATTLEFIELD_HEIGHT;
    battlefield->width = BATTLEFIELD_WIDTH;

    return battlefield;
}

void render(Battlefield *battlefield, Plane *plane, EnemyList *enemies, ProjectileList* planeProjectiles, ProjectileList* enemyProjectiles) {
    printf("\033[2J\033[1;1H\n"); // Limpar terminal
    char* screen = malloc(sizeof(char) * (battlefield->height + 2) * (battlefield->width + 2));
    zeroFill(screen);

    drawScreenTop(screen, battlefield);
    drawGameBoard(screen, battlefield, plane, enemies, planeProjectiles, enemyProjectiles);
    drawGameBoardBottom(screen, battlefield);
    // drawGameInfo(screen, battlefield, plane, enemies);

    printf("%s\n", screen);
    free(screen);
}

void update(Battlefield *battlefield, Plane *plane, EnemyList *enemies, ProjectileList* planeProjectiles, ProjectileList* enemyProjectiles) {
    moveProjectiles(battlefield, planeProjectiles);
    moveProjectiles(battlefield, enemyProjectiles);

    hitEnemies(planeProjectiles, enemies, plane);
    hitPlayerWithEnemy(enemies, plane);
    hitPlayer(enemyProjectiles, plane);

    moveEnemies(battlefield, enemies, plane);

    deleteEnemiesOutOfBounds(battlefield, enemies, plane);
    deleteProjectilesOutOfBounds(battlefield, planeProjectiles);
    deleteProjectilesOutOfBounds(battlefield, enemyProjectiles);
    spawnNewEnemies(battlefield, enemies);
}

void movePlane(Plane *plane, int xVariation, int yVariation) {
    if ((plane->x + xVariation >= 0) && (plane->x + xVariation < BATTLEFIELD_WIDTH)) {
        plane->x = plane->x + xVariation;
    }

    if ((plane->y + yVariation >= 0) && (plane->y + yVariation < BATTLEFIELD_HEIGHT)) {
        plane->y = plane->y + yVariation;
    }
}

void drawScreenTop(char *screen, Battlefield *battlefield) {
    appendStr(screen, DOUBLE_UPPER_LEFT_CORNER);
    for (int i = 0; i < battlefield->width; i++) {
        appendStr(screen, DOUBLE_HORIZONTAL);
    }

    appendStr(screen, DOUBLE_UPPER_RIGHT_CORNER);
    appendStr(screen, "\n");
}

void drawGameBoard(char *screen, Battlefield *battlefield, Plane *plane, EnemyList *enemies, ProjectileList* planeProjectiles, ProjectileList* enemyProjectiles) {
    int i, j;
    // char mat[BATTLEFIELD_HEIGHT][BATTLEFIELD_WIDTH];
    char*** mat;
    mat = malloc(sizeof(char**) * battlefield->height);
    for (i = 0; i < battlefield->height; i++) {
        mat[i] = malloc(sizeof(char*) * battlefield->width);
        for (j = 0; j < battlefield->width; j++) {
            mat[i][j] = malloc(sizeof(char) * 4);
            strcpy(mat[i][j], " ");
            // mat[i][j] = ' ';
        }
    }

    // draw enemies
    renderEnemies(mat, enemies);

    // draw player plane
    renderPlane(mat, plane, battlefield->height, battlefield->width);

    // draw projectiles
    renderProjectiles(mat, planeProjectiles, battlefield->height, battlefield->width);
    renderProjectiles(mat, enemyProjectiles, battlefield->height, battlefield->width);

    for (i = 0; i < battlefield->height; i++) {
        appendStr(screen, DOUBLE_VERTICAL);
        for (j = 0; j < battlefield->width; j++) {
            appendStr(screen, mat[i][j]);
        }
        appendStr(screen, DOUBLE_VERTICAL);
        appendStr(screen, "\n");
    }
    for (i = 0; i < battlefield->height; i++) {
        for (j = 0; j < battlefield->width; j++) {
            free(mat[i][j]);
        }
        free(mat[i]);
    }
    free(mat);
}

void drawGameBoardBottom(char *screen, Battlefield *battlefield)
{
    // ╚═════════════════╝
    appendStr(screen, DOUBLE_LOWER_LEFT_CORNER);
    for (int i = 0; i < battlefield->width; i++) {
        appendStr(screen, DOUBLE_HORIZONTAL);
    }

    appendStr(screen, DOUBLE_LOWER_RIGHT_CORNER);
    appendStr(screen, "\n");
}

void renderEnemies(char *mat, EnemyList *enemies) {
    Enemy* enemy = enemies->head;
    while (NULL != enemy) {
        mat[enemy->y + enemy->x] = ENEMY_SPRITE;
        enemy = enemy->next;
    }
}

void renderPlane(char ***mat, Plane *plane, int height, int width) {
    strcpy(mat[plane->y][plane->x], PLANE_HEAD);
}

void renderProjectiles(char ***mat, ProjectileList *projectileList, int height, int width) {
    Projectile* projectile = projectileList->head;
    while (NULL != projectile) {
        if ((projectile->x > 0) && (projectile->x <= width) && (projectile->y > 0) && (projectile->y <= height)) {
            strcpy(mat[projectile->y][projectile->x], PROJECTILE);
        }
        projectile = projectile->next;
    }
}

void zeroFill(char* ch) {
    for (int i = 0; i < strlen(ch); i++)
        ch[i] = 0;
}

void appendStr(char* dest, char* src)
{
    dest = strcat(dest, src);
}

void moveEnemies(Battlefield* battlefield, EnemyList* enemies, Plane* plane) {
    Enemy* enemy = enemies->head;
    while (NULL != enemy) {
        enemy->x += enemy->stepX;
        enemy->y += enemy->stepY;
        enemy = enemy->next;
    }
}

void moveProjectiles(Battlefield* battlefield, ProjectileList* projectileList) {
    Projectile* projectile = projectileList->head;
    while (NULL != projectile) {
        projectile->x += projectile->stepX;
        projectile->y += projectile->stepY;
        projectile = projectile->next;
    }
}

void hitEnemies(ProjectileList* projectileList, EnemyList* enemies, Plane* plane) {
    Projectile* projectile = projectileList->head;
    Projectile* nextProjectile;
    Enemy* enemy;
    Enemy* nextEnemy;
    while (NULL != projectile){
        enemy = enemies->head;
        nextProjectile = projectile->next;
        while (NULL != enemy) {
            nextEnemy = enemy->next;

            if (projectileAndEnemyAreColliding(projectile, enemy)) {
                removeEnemyNode(enemies, enemy);
                removeProjectileNode(projectileList, projectile);
                plane->score += 10;
            }

            enemy = nextEnemy;
        }
        projectile = nextProjectile;
    }
}

void hitPlayerWithEnemy(EnemyList* enemies, Plane* plane) {
    Enemy* enemy = enemies->head;
    Enemy* nextEnemy;
    while (NULL != enemy) {
        nextEnemy = enemy->next;
        if (enemyAndPlaneAreColliding(enemy, plane)) {
            removeEnemyNode(enemies, enemy);
            plane->lives--;
        }
        enemy = nextEnemy;
    }
}

void hitPlayer(ProjectileList* projectileList, Plane* plane) {
    Projectile* projectile = projectileList->head;
    Projectile* nextProjectile;
    while (NULL != projectile) {
        nextProjectile = projectile->next;
        if (projectileAndPlaneAreColliding(projectile, plane)) {
            removeProjectileNode(projectileList, projectile);
            plane->lives--;
        }
        projectile = nextProjectile;
    }
}

void deleteEnemiesOutOfBounds(Battlefield* battlefield, EnemyList* enemies, Plane* plane) {
    Enemy* enemy = enemies->head;
    Enemy* nextEnemy;
    while (NULL != enemy) {
        nextEnemy = enemy->next;
        if ((enemy->x < 0) || (enemy->x >= battlefield->width)  || (enemy->y < 0) ||  (enemy->y >= battlefield->height)) {
            // Atingiu o rodapé, perde 1 vida
            if (enemy->y >= battlefield->height) {
                plane->lives--;
                removeEnemyNode(enemies, enemy);
            }
        }
        enemy = nextEnemy;
    }
}

void deleteProjectilesOutOfBounds(Battlefield* battlefield, ProjectileList* projectileList) {
    Projectile* projectile = projectileList->head;
    Projectile* nextProjectile;
    while (NULL != projectile) {
        nextProjectile = projectile->next;
        if ((projectile->x < 0) || (projectile->x >= battlefield->width)  || (projectile->y < 0) ||  (projectile->y >= battlefield->height)) {

            projectile = projectile->next;
            removeProjectileNode(projectileList, projectile->prev);
        }
        projectile = nextProjectile;
    }
}

bool projectileAndEnemyAreColliding(Projectile* projectile, Enemy* enemy) {
    return ((projectile->x == enemy->x) && (projectile->y == enemy->y));
}

bool projectileAndPlaneAreColliding(Projectile* projectile, Plane* plane) {
    return ((projectile->x == plane->x) && (projectile->y == plane->y));
}

bool enemyAndPlaneAreColliding(Enemy* enemy, Plane* plane) {
    return ((enemy->x == plane->x) && (enemy->y == plane->y));
}

void spawnNewEnemies(Battlefield* battlefield, EnemyList* enemies) {
    if (rand() % 100 <= SPAWN_CHANCE) {
        insertEnemyNode(enemies, createEnemy(rand() % battlefield->width, 0, (rand() % 3) - 1, 1));
    }
}