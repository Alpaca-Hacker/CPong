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

void CheckHit(Rectangle rec);

void UpdateBall(float deltaTime);

void UpdateEnemy(float deltaTime);

void UpdatePlayer(float deltaTime);

typedef struct Ball{
    Vector2 position;
    Vector2 velocity;
    float radius;
    int hits;
} Ball;

typedef struct Player{
    Vector2 position;
    float speed;
    int score;
} Player;

Ball ball = {0};
Player player = {0};
Player enemy = {0};

Rectangle playerRec = {0};
Rectangle enemyRec = {0};

int gameStart() {
    init();
    gameLoop();
    end();
    return 0;
}

void init() {

    SetTargetFPS(FPS);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong!");

    ball.position.x = 100.0f;
    ball.position.y = 100.0f;
    ball.velocity.x = 3.0f;
    ball.velocity.y = 3.0f;
    ball.radius = RADIUS;

    player.position.x = 30;
    player.position.y = SCREEN_HEIGHT / 2 - BAT_HEIGHT / 2;
    player.speed = 10;

    enemy.position.x = SCREEN_WIDTH - 55;
    enemy.position.y = SCREEN_HEIGHT / 2 - BAT_HEIGHT / 2;
    enemy.speed = 5;

    playerRec.width = 25;
    playerRec.height = BAT_HEIGHT;
    enemyRec.width = 25;
    enemyRec.height = BAT_HEIGHT;
}

void gameLoop() {
    while (!WindowShouldClose()){
        gameUpdate();
        gameDraw();
    }
}

void gameUpdate() {
    float deltaTime = GetFrameTime();

    UpdateEnemy(deltaTime);
    UpdateBall(deltaTime);
    UpdatePlayer(deltaTime);
}

void UpdatePlayer(float deltaTime) {
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        player.position.y += player.speed * (deltaTime * FPS);
    } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        player.position.y -= player.speed * (deltaTime * FPS);
    }

    player.position.y = clampF(0, player.position.y, SCREEN_HEIGHT - BAT_HEIGHT);
    playerRec.x = player.position.x;
    playerRec.y = player.position.y;
}

void UpdateEnemy(float deltaTime) {
    float move = 0.0f;
    if (ball.position.y > enemy.position.y){
        move = enemy.speed * (deltaTime * FPS);
    }
    if (ball.position.y < enemy.position.y){
        move = -enemy.speed * (deltaTime * FPS);
    }

    enemy.position.y += move;
    enemy.position.y =  clampF(0, enemy.position.y, SCREEN_HEIGHT - BAT_HEIGHT);
    enemyRec.x = enemy.position.x;
    enemyRec.y = enemy.position.y;
}

void UpdateBall(float deltaTime) {
    ball.position.x += ball.velocity.x * (deltaTime * FPS);
    ball.position.y += ball.velocity.y * (deltaTime * FPS);

    if (ball.position.x <= 60){
        CheckHit(playerRec);
    }

    if (ball.position.x >= SCREEN_WIDTH - 60){
        CheckHit(enemyRec);
    }

    if (ball.position.x < ball.radius || ball.position.x > SCREEN_WIDTH - ball.radius){
        ball.velocity.x = -ball.velocity.x;
        ball.hits ++;
        ball.position.x = clampF(ball.radius, ball.position.x, SCREEN_WIDTH - ball.radius);
    }

    if (ball.position.y < ball.radius || ball.position.y > SCREEN_HEIGHT - ball.radius){
        ball.velocity.y = -ball.velocity.y;
        ball.hits++;
        ball.position.y = clampF(ball.radius, ball.position.y, SCREEN_HEIGHT - ball.radius);
    }

    if (ball.hits >= 5){
        ball.velocity.x < 0 ? ball.velocity.x--: ball.velocity.x++;
        ball.velocity.y < 0 ? ball.velocity.y-- : ball.velocity.y++;
        ball.hits = 0;
    }
}

void CheckHit(Rectangle rec) {
    if (CheckCollisionCircleRec(ball.position, ball.radius, rec)){
        ball.velocity.x = -ball.velocity.x;
        ball.hits++;
        // If ball hits edge of bat bounce away
        if (ball.position.y < rec.y+BAT_HEIGHT/6 && ball.velocity.y > 0){
            ball.velocity.y = -ball.velocity.y;
        }else if (ball.position.y > rec.y+(BAT_HEIGHT - BAT_HEIGHT/6) && ball.velocity.y < 0)
        {
            ball.velocity.y = -ball.velocity.y;
        }
    }
}

void gameDraw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawCircleV(ball.position, ball.radius, PINK);
    DrawRectangleRec(playerRec, RED);
    DrawRectangleRec(enemyRec, BLUE);

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



