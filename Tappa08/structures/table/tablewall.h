#ifndef TABLEWALL_H
#define TABLEWALL_H
#include <SFML/Graphics.hpp>
#include "../../collisions/collisions.h"
#include "pocket.h"

class TableWall {
public:
    TableWall(unsigned id, Pocket* left, Pocket* right, sf::Vector2f direction);
    void draw(sf::RenderWindow& window);
    void resize();
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    std::string to_string() const;
    sf::FloatRect getBoundBox() const;
    std::vector<sf::Vector2f> getHitbox() const;
private:
    sf::Vector2f direction;
    Pocket* left;
    Pocket* right;
    unsigned id;
    sf::ConvexShape shape;
};

#endif
