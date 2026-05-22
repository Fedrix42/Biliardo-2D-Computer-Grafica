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
    sf::Vector2f get_position() const;
    std::string to_string() const;
    sf::FloatRect get_bound_box() const;
    std::vector<sf::Vector2f> get_hitbox() const;
private:
    sf::Vector2f direction;
    Pocket* left;
    Pocket* right;
    unsigned id;
    sf::ConvexShape shape;
};

#endif
