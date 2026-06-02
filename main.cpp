#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

enum GameState {
    START_SCREEN,
    PLAYING,
    GAME_OVER
};

const int screenWidth = 800;
const int screenHeight = 600;

struct Particle {
    Vector2 position;
    Vector2 velocity;
    float life;
    Color color;
};

Vector2 GetRandomSpawnPosition() {
    int side = rand() % 4;
    Vector2 spawnPos = { 0.0f, 0.0f };

    switch (side) {
        case 0:
            spawnPos.x = (float)(rand() % screenWidth);
            spawnPos.y = -20.0f;
            break;
        case 1:
            spawnPos.x = (float)(rand() % screenWidth);
            spawnPos.y = (float)(screenHeight + 20);
            break;
        case 2:
            spawnPos.x = -20.0f;
            spawnPos.y = (float)(rand() % screenHeight);
            break;
        case 3:
            spawnPos.x = (float)(screenWidth + 20);
            spawnPos.y = (float)(rand() % screenHeight);
            break;
    }

    return spawnPos;
}

std::vector<Bullet> bullets;
std::vector<Particle> particles;
int score = 0;

int main(void) {
    const char* windowTitle = "Neon Survivor";
    const int targetFPS = 60;

    InitWindow(screenWidth, screenHeight, windowTitle);
    SetTargetFPS(targetFPS);

    GameState currentState = START_SCREEN;

    Player player;
    std::vector<Enemy> enemies;
    float spawnTimer = 0.0f;
    const float spawnInterval = 0.15f;
    float shootTimer = 0.0f;
    const float shootInterval = 0.2f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            switch (currentState) {
                case START_SCREEN:
                    currentState = PLAYING;
                    enemies.clear();
                    bullets.clear();
                    particles.clear();
                    score = 0;
                    break;
                case PLAYING:
                    currentState = GAME_OVER;
                    enemies.clear();
                    bullets.clear();
                    particles.clear();
                    break;
                case GAME_OVER:
                    currentState = START_SCREEN;
                    enemies.clear();
                    bullets.clear();
                    particles.clear();
                    score = 0;
                    break;
            }
        }

        if (currentState == PLAYING) {
            player.Update();

            spawnTimer += GetFrameTime();
            if (spawnTimer >= spawnInterval) {
                spawnTimer = 0.0f;
                Vector2 spawnPos = GetRandomSpawnPosition();
                enemies.push_back(Enemy(spawnPos));
            }

            shootTimer += GetFrameTime();
            if (shootTimer >= shootInterval && !enemies.empty()) {
                Vector2 playerCenter = { 
                    player.position.x + player.size / 2, 
                    player.position.y + player.size / 2 
                };

                float minDist = INFINITY;
                Vector2 targetPos = { 0.0f, 0.0f };

                for (size_t i = 0; i < enemies.size(); i++) {
                    if (!enemies[i].active) continue;
                    
                    float dx = enemies[i].position.x - playerCenter.x;
                    float dy = enemies[i].position.y - playerCenter.y;
                    float dist = sqrt(dx * dx + dy * dy);
                    
                    if (dist < minDist) {
                        minDist = dist;
                        targetPos = enemies[i].position;
                    }
                }

                if (minDist != INFINITY) {
                    float dx = targetPos.x - playerCenter.x;
                    float dy = targetPos.y - playerCenter.y;
                    float dist = sqrt(dx * dx + dy * dy);
                    
                    Vector2 velocity = {
                        (dx / dist) * 600.0f,
                        (dy / dist) * 600.0f
                    };
                    
                    bullets.push_back(Bullet(playerCenter, velocity));
                }

                shootTimer = 0.0f;
            }

            for (size_t i = 0; i < bullets.size(); i++) {
                bullets[i].Update();
            }

            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].Update(player.position);
            }

            for (size_t i = 0; i < particles.size(); i++) {
                particles[i].position.x += particles[i].velocity.x * GetFrameTime();
                particles[i].position.y += particles[i].velocity.y * GetFrameTime();
                particles[i].life -= GetFrameTime() * 2.0f;
            }

            for (size_t i = 0; i < bullets.size(); i++) {
                if (!bullets[i].active) continue;
                
                for (size_t j = 0; j < enemies.size(); j++) {
                    if (!enemies[j].active) continue;
                    
                    if (CheckCollisionCircles(
                        bullets[i].position, bullets[i].radius,
                        enemies[j].position, enemies[j].radius)) {
                        bullets[i].active = false;
                        enemies[j].active = false;
                        score += 10;

                        for (int k = 0; k < 15; k++) {
                            Particle p;
                            p.position = enemies[j].position;
                            p.velocity.x = (float)GetRandomValue(-100, 100);
                            p.velocity.y = (float)GetRandomValue(-100, 100);
                            p.life = 1.0f;
                            p.color = RED;
                            particles.push_back(p);
                        }
                    }
                }
            }

            Rectangle playerRect = {
                player.position.x, player.position.y,
                player.size, player.size
            };

            for (size_t i = 0; i < enemies.size(); i++) {
                if (!enemies[i].active) continue;
                
                if (CheckCollisionCircleRec(
                    enemies[i].position, enemies[i].radius, playerRect)) {
                    currentState = GAME_OVER;
                    enemies.clear();
                    bullets.clear();
                    particles.clear();
                    break;
                }
            }

            bullets.erase(
                std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& b) { return !b.active; }),
                bullets.end()
            );

            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [](const Enemy& e) { return !e.active; }),
                enemies.end()
            );

            particles.erase(
                std::remove_if(particles.begin(), particles.end(),
                    [](const Particle& p) { return p.life <= 0.0f; }),
                particles.end()
            );
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (currentState == START_SCREEN) {
            const int textSize = 24;
            const char* displayText = "Press ENTER to Start";
            int textWidth = MeasureText(displayText, textSize);
            int textX = (screenWidth - textWidth) / 2;
            int textY = screenHeight / 2;
            DrawText(displayText, textX, textY, textSize, WHITE);

            const char* line1 = "Controls: WASD or Arrows to Move";
            const char* line2 = "Combat: Auto-aim & Shoot";
            const char* line3 = "Goal: Survive the Red Swarm!";
            int lineY = textY + 40;
            int lineWidth = MeasureText(line1, 20);
            DrawText(line1, (screenWidth - lineWidth) / 2, lineY, 20, LIGHTGRAY);
            lineWidth = MeasureText(line2, 20);
            DrawText(line2, (screenWidth - lineWidth) / 2, lineY + 30, 20, LIGHTGRAY);
            lineWidth = MeasureText(line3, 20);
            DrawText(line3, (screenWidth - lineWidth) / 2, lineY + 60, 20, LIGHTGRAY);
        }
        else if (currentState == PLAYING) {
            player.Draw();

            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].Draw();
            }

            for (size_t i = 0; i < bullets.size(); i++) {
                bullets[i].Draw();
            }

            for (size_t i = 0; i < particles.size(); i++) {
                if (particles[i].life > 0.0f) {
                    DrawCircleV(particles[i].position, 2.0f, Fade(RED, particles[i].life));
                }
            }

            char scoreText[32];
            sprintf(scoreText, "Score: %d", score);
            DrawText(scoreText, 10, 10, 20, WHITE);
        }
        else if (currentState == GAME_OVER) {
            const int textSize = 24;
            const char* displayText = "Game Over! Press ENTER";
            int textWidth = MeasureText(displayText, textSize);
            int textX = (screenWidth - textWidth) / 2;
            int textY = screenHeight / 2;
            DrawText(displayText, textX, textY, textSize, WHITE);

            char scoreText[32];
            sprintf(scoreText, "Final Score: %d", score);
            int scoreWidth = MeasureText(scoreText, 20);
            int scoreX = (screenWidth - scoreWidth) / 2;
            DrawText(scoreText, scoreX, textY + 40, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}