#include "bullet.h"

const int screenWidth = 800;
const int screenHeight = 600;

Bullet::Bullet(Vector2 pos, Vector2 vel) {
    position = pos;
    velocity = vel;
    radius = 4.0f;
    color = YELLOW;
    active = true;
}

void Bullet::Update() {
    if (!active) return;

    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    if (position.x < -20.0f || position.x > screenWidth + 20.0f ||
        position.y < -20.0f || position.y > screenHeight + 20.0f) {
        active = false;
    }
}

void Bullet::Draw() {
    if (!active) return;
    DrawCircleV(position, radius, color);
}
