//
// Created by paul on 13/08/2021.
//
#include <raylib.h>

#include "headers/game.h"
#include "headers/constants.h"

void init();
void gameLoop();
void gameUpdate();
void gameDraw();
void end();

float clampF(const float min, const float num, const float max);

typedef struct Ball{
    Vector2 position;
    Vector2 velocity;
    float radius;
    int hits;
} Ball;

Ball ball = {0};

int gameStart() {
    init();
    gameLoop();
    end();
    return 0;
}

void init() {

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Pong!");
    ball.position.x = 100.0f;
    ball.position.y = 100.0f;

    ball.velocity.x = 3.0f;
    ball.velocity.y = 3.0f;

    ball.radius = radius;
}

void gameLoop() {

    while (!WindowShouldClose()){
        gameUpdate();
        BeginDrawing();

        gameDraw();

    }
}


void gameUpdate() {
    float deltaTime = GetFrameTime();

    ball.position.x += ball.velocity.x * (deltaTime * FPS);
    ball.position.y += ball.velocity.y * (deltaTime * FPS);

    if (ball.position.x < radius || ball.position.x > screenWidth - radius){
        ball.velocity.x = -ball.velocity.x;
        ball.hits ++;
        ball.position.x = clampF(radius, ball.position.x, screenWidth - radius);
    }
    if (ball.position.y < radius || ball.position.y > screenHeight - radius){
        ball.velocity.y = -ball.velocity.y;
        ball.hits++;
        ball.position.y = clampF(radius, ball.position.y, screenHeight - radius);
    }

    if (ball.hits >= 5){
        ball.velocity.x < 0 ? ball.velocity.x--: ball.velocity.x++;
        ball.velocity.y < 0 ? ball.velocity.y-- : ball.velocity.y++;
        ball.hits = 0;
    }

}

void gameDraw() {
    ClearBackground(RAYWHITE);

    DrawCircleV(ball.position, ball.radius, PINK);

    EndDrawing();
}

void end() {
    CloseWindow();
}

float clampF(const float low, const float num, const float max) {
    if (num > max) {
        return num < low ? low : max;
    } else {
        return num < low ? low : num;
    }
}



