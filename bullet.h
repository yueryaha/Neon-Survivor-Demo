#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

class Bullet {
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool active;
    Color color;

    Bullet(Vector2 pos, Vector2 vel);
    void Update();
    void Draw();
};

#endif
