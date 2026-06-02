#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Vector2 position;
    float speed;
    float size;
    Color color;

    Player();
    void Update();
    void Draw();
};

#endif
