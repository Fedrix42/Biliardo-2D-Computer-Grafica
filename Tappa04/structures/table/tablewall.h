#ifndef TABLEWALL_H
#define TABLEWALL_H
#include <SFML/Graphics.hpp>
#include "../collider.h"
#include "pocket.h"

class TableWall : public Collider {
public:
    TableWall(unsigned id, Pocket left, Pocket right, sf::Vector2f direction);
    void draw(sf::RenderWindow& window);
    std::vector<sf::Vector2f> getHitbox() const override;
    sf::Vector2f getPosition() const override;
    sf::Vector2f getSpeed() const override;
    void setPosition(sf::Vector2f pos) override;
    void setSpeed(sf::Vector2f speed) override;
    std::string to_string() const override;
    sf::FloatRect getBoundBox() const override;
private:
    unsigned id;
    sf::ConvexShape shape;
};

#endif
