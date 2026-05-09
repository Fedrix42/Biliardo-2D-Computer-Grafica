#ifndef POCKET_H
#define POCKET_H
#include <SFML/Graphics.hpp>
#include "../ball.h"
class Pocket { // Buca
public:
    Pocket(unsigned id, sf::Vector2u table_size);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    float getRadius();

private:
    unsigned id;
    sf::CircleShape shape;
    std::vector<Ball*> balls;
};

#endif
