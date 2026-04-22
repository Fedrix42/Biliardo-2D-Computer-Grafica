#include "state.h"

State::State(unsigned window_width, unsigned window_height){
    this->ball = new Ball({0, 0});
    this->paddle = new Paddle({0, 0});
}

void State::draw(sf::RenderWindow& window){
    this->ball->draw(window);
    this->paddle->draw(window);
}
