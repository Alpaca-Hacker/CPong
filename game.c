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

typedef struct Player{
    Vector2 position;
    float speed;
} Player;

Ball ball = {0};
Player player = {0};

Rectangle playerRec = {0};

int gameStart() {
    init();
    gameLoop();
    end();
    return 0;
}

void init() {

    SetTargetFPS(FPS);

    InitWindow(screenWidth, screenHeight, "Pong!");

    ball.position.x = 100.0f;
    ball.position.y = 100.0f;
    ball.velocity.x = 3.0f;
    ball.velocity.y = 3.0f;
    ball.radius = radius;

    player.position.x = 30;
    player.position.y = screenHeight/2- 75;
    player.speed = 5;

    playerRec.width = 25;
    playerRec.height = 150;
}

void gameLoop() {
    while (!WindowShouldClose()){
        gameUpdate();
        gameDraw();
    }
}

void gameUpdate() {
    float deltaTime = GetFrameTime();
    playerRec.x = player.position.x;
    playerRec.y = player.position.y;
    ball.position.x += ball.velocity.x * (deltaTime * FPS);
    ball.position.y += ball.velocity.y * (deltaTime * FPS);

    if (ball.position.x <= 60 && CheckCollisionCircleRec(ball.position, ball.radius, playerRec)){
        ball.velocity.x = -ball.velocity.x;
        ball.hits++;
        if (ball.position.y < player.position.y+25 && ball.velocity.y > 0){
            ball.velocity.y = -ball.velocity.y;
        }else if (ball.position.y > player.position.y+125 && ball.velocity.y < 0)
        {
            ball.velocity.y = -ball.velocity.y;
        }
    }

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

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        player.position.y += player.speed * (deltaTime * FPS);
    } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        player.position.y -= player.speed * (deltaTime * FPS);
    }

    player.position.y = clampF(0, player.position.y, screenHeight - 150);

    if (ball.hits >= 5){
        ball.velocity.x < 0 ? ball.velocity.x--: ball.velocity.x++;
        ball.velocity.y < 0 ? ball.velocity.y-- : ball.velocity.y++;
        ball.hits = 0;
    }

}

void gameDraw() {
    BeginDrawing();



    ClearBackground(RAYWHITE);
    DrawCircleV(ball.position, ball.radius, PINK);
    DrawRectangleRec(playerRec, RED);
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



