//
// Created by paul on 14/08/2021.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#endif //PONG_BALL_H

typedef struct Ball{
    Vector2 position;
    Vector2 velocity;
    float radius;
    int hits;
    Sound hitFX[2];
} Ball;

void initBall(struct Ball *ball);

void updateBall(Ball *ball, float deltaTime);

void checkHit(Ball *ball, Rectangle rec);

