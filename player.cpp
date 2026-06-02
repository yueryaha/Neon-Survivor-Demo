#include "player.h"

const int screenWidth = 800;
const int screenHeight = 600;

Player::Player() {
    position = { 400.0f, 300.0f };
    speed = 300.0f;
    size = 20.0f;
    color = BLUE;
}

void Player::Update() {
    float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        position.y -= speed * deltaTime;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        position.y += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        position.x -= speed * deltaTime;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        position.x += speed * deltaTime;
    }

    if (position.x < 0.0f) {
        position.x = 0.0f;
    }

    if (position.x > (float)screenWidth - size) {
        position.x = (float)screenWidth - size;
    }

    if (position.y < 0.0f) {
        position.y = 0.0f;
    }

    if (position.y > (float)screenHeight - size) {
        position.y = (float)screenHeight - size;
    }
}

void Player::Draw() {
    DrawRectangleV(position, { size, size }, color);
}