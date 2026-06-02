#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemy {
public:
    Vector2 position;
    float speed;
    float radius;
    Color color;
    bool active;

    Enemy();
    Enemy(Vector2 spawnPos);
    void Update(Vector2 playerPos);
    void Draw();
};

#endif
