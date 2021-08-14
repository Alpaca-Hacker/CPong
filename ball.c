//
// Created by paul on 14/08/2021.
//

#include "headers/constants.h"
#include "headers/utility.h"
#include <raylib.h>
#include "headers/ball.h"


void initBall(struct Ball *ball) {
    ball->position.x = 100.0f;
    ball->position.y = 100.0f;
    ball->velocity.x = 3.0f;
    ball->velocity.y = 3.0f;
}

void updateBall(Ball *ball, float deltaTime) {
    ball->position.x += ball->velocity.x * (deltaTime * FPS);
    ball->position.y += ball->velocity.y * (deltaTime * FPS);

    if (ball->position.y < ball->radius || ball->position.y > SCREEN_HEIGHT - ball->radius){
        ball->velocity.y = -ball->velocity.y;
        ball->hits++;
        ball->position.y = clampF(ball->radius, ball->position.y, SCREEN_HEIGHT - ball->radius);
    }

    if (ball->hits >= 5){
        ball->velocity.x < 0 ? ball->velocity.x--: ball->velocity.x++;
        ball->velocity.y < 0 ? ball->velocity.y-- : ball->velocity.y++;
        ball->hits = 0;
    }
}

void checkHit(Ball *ball, Rectangle rec) {
    if (CheckCollisionCircleRec(ball->position, ball->radius, rec)){
        ball->velocity.x = -ball->velocity.x;
        ball->hits++;
        // If ball hits edge of bat bounce away
        if (ball->position.y < rec.y+BAT_HEIGHT/6 && ball->velocity.y > 0){
            ball->velocity.y = -ball->velocity.y;
        }else if (ball->position.y > rec.y+(BAT_HEIGHT - BAT_HEIGHT/6) && ball->velocity.y < 0)
        {
            ball->velocity.y = -ball->velocity.y;
        }
    }
}