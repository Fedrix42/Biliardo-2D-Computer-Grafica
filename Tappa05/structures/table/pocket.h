#ifndef POCKET_H
#define POCKET_H
#include <SFML/Graphics.hpp>
#include "../ball.h"

class Pocket { // Buca
public:
    Pocket(unsigned int id, sf::Vector2f table_size, sf::Vector2f offset);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    float getRadius();
    void resize(sf::Vector2f table_size, sf::Vector2f offset);
private:
    unsigned id;
    sf::CircleShape shape;
    std::vector<Ball*> balls;
};

#endif
