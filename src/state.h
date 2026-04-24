#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class State {
public:
    State(unsigned window_width, unsigned window_height);
    void draw(sf::RenderWindow& window);
};


#endif