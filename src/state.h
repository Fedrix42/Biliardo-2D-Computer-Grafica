#ifndef STATE_H
#define STATE_H

#include "ball.h"
#include "paddle.h"

class State {
public:
    Ball* ball;
    Paddle* paddle;

    State(unsigned window_width, unsigned window_height);
    void draw(sf::RenderWindow& window);
};

#endif