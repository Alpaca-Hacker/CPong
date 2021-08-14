//
// Created by paul on 13/08/2021.
//
#include <raylib.h>
#include <stdio.h>

#include "headers/game.h"
#include "headers/constants.h"
#include "headers/ball.h"
#include "headers/utility.h"

void init();
void gameLoop();
void gameUpdate();
void gameDraw();
void end();

void updateEnemy(float deltaTime);
void updatePlayer(float deltaTime);

void checkScore();

typedef struct Player{
    Vector2 position;
    float speed;
} Player;

int playerScore = 0;
int enemyScore = 0;

struct Ball ball = {0};
Player player = {0};
Player enemy = {0};

Rectangle playerRec = {0};
Rectangle enemyRec = {0};

char score[10];
int textLen;

int gameStart() {
    init();
    gameLoop();
    end();
    return 0;
}

void init() {

    SetTargetFPS(FPS);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong!");

    initBall(&ball);

    ball.radius = RADIUS;

    player.position.x = BAT_WIDTH + 5;
    player.position.y = SCREEN_HEIGHT / 2 - BAT_HEIGHT / 2;
    player.speed = 10;

    enemy.position.x = SCREEN_WIDTH - (2 * BAT_WIDTH + 5);
    enemy.position.y = SCREEN_HEIGHT / 2 - BAT_HEIGHT / 2;
    enemy.speed = 5;

    playerRec.width = BAT_WIDTH;
    playerRec.height = BAT_HEIGHT;
    enemyRec.width = BAT_WIDTH;
    enemyRec.height = BAT_HEIGHT;

    sprintf(score, "%02d     %02d", playerScore, enemyScore);
    textLen = MeasureText(score, 100);
}

void gameLoop() {
    while (!WindowShouldClose()){
        gameUpdate();
        gameDraw();
    }
}

void gameUpdate() {
    float deltaTime = GetFrameTime();

    updateEnemy(deltaTime);
    updateBall(&ball, deltaTime);
    updatePlayer(deltaTime);

    if (ball.position.x <= 60){
        checkHit(&ball, playerRec);
    }

    if (ball.position.x >= SCREEN_WIDTH - 60){
        checkHit(&ball, enemyRec);
    }

    checkScore();
}

void checkScore() {

    if (ball.position.x < ball.radius) {
        ball.hits = 0;
        enemyScore++;
        initBall(&ball);
    }

    if (ball.position.x > SCREEN_WIDTH - ball.radius){
        ball.hits = 0;
        playerScore ++;
        initBall(&ball);
    }
}

void updatePlayer(float deltaTime) {
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        player.position.y += player.speed * (deltaTime * FPS);
    } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        player.position.y -= player.speed * (deltaTime * FPS);
    }

    player.position.y = clampF(0, player.position.y, SCREEN_HEIGHT - BAT_HEIGHT);
    playerRec.x = player.position.x;
    playerRec.y = player.position.y;
}

void updateEnemy(float deltaTime) {
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

void gameDraw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawCircleV(ball.position, ball.radius, PINK);
    DrawRectangleRec(playerRec, RED);
    DrawRectangleRec(enemyRec, BLUE);

    sprintf(score, "%02d     %02d", playerScore, enemyScore);

    DrawText(score, (SCREEN_WIDTH-textLen)/2, 30, 100, DARKBLUE);

    EndDrawing();
}

void end() {
    CloseWindow();
}





