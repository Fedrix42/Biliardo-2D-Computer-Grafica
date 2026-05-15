#ifndef CUE_H
#define CUE_H
#include "ball.h"
#include <SFML/Graphics.hpp>

enum CueType {
    ANCHOR,
    FREE
};

class Cue {
public:
    Cue(sf::Vector2f position);
    void update(const sf::Event::MouseMoved* moved);
    void draw(sf::RenderWindow& window);
    Ball shot(); // Restituisce una pallina virtuale
    bool hide;
    Ball* anchor;
    CueType type = CueType::ANCHOR;
private:
    float mass = 0.5; // 0.5 kg
    sf::RectangleShape body;
    sf::CircleShape tip;

};

#endif
