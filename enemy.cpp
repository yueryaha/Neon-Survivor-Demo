#include "enemy.h"
#include <cmath>

Enemy::Enemy() {
    position = { 0.0f, 0.0f };
    speed = 180.0f;
    radius = 10.0f;
    color = RED;
    active = true;
}

Enemy::Enemy(Vector2 spawnPos) {
    position = spawnPos;
    speed = 180.0f;
    radius = 10.0f;
    color = RED;
    active = true;
}

void Enemy::Update(Vector2 playerPos) {
    if (!active) return;

    // Calculate direction vector towards player
    float dx = playerPos.x - position.x;
    float dy = playerPos.y - position.y;

    // Calculate distance
    float distance = sqrt(dx * dx + dy * dy);

    // Normalize and move towards player
    if (distance > 0.0f) {
        float normalizedX = dx / distance;
        float normalizedY = dy / distance;

        position.x += normalizedX * speed * GetFrameTime();
        position.y += normalizedY * speed * GetFrameTime();
    }
}

void Enemy::Draw() {
    if (!active) return;

    DrawCircleV(position, radius, color);
}
