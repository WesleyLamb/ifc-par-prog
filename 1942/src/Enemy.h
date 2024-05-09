#ifndef Enemy_h
#define Enemy_h

#define SPAWN_CHANCE 5
#define ENEMY_SPRITE 'v'

typedef struct sEnemy {
    int x;
    int y;
    int stepX;
    int stepY;
    struct sEnemy* prev;
    struct sEnemy* next;
} Enemy;

Enemy* createEnemy(int, int, int, int);

#endif