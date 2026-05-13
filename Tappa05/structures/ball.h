#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "collider.h"

enum BallIDRange {
    SMOOTH_START = 1,
    SMOOTH_STOP = 7,
    BLACK = 8,
    STRIPED_START = 9,
    STRIPED_STOP = 15,
    WHITE = 16
};

class Ball : public Collider {
public:
    Ball(unsigned id, float pocket_radius, float tableFrictionCoeff, sf::Vector2f pos);
    void draw(sf::RenderWindow& window);
    void update(sf::Time current_t);
    float getRadius();
    void resize(sf::Vector2f factors, float new_pocket_radius, sf::Vector2f new_offset, sf::Vector2f old_offset);
    float getMass() const override;
    sf::Vector2f getPosition() const override;
    sf::Vector2f getSpeed() const override;
    void setPosition(sf::Vector2f pos) override;
    void setSpeed(sf::Vector2f speed) override;
    std::string to_string() const override;
    float getDecelleration() const override;
private:
    std::vector<sf::Vector2f> getHitbox() const override;
    sf::FloatRect getBoundBox() const override;
    sf::Vector2f speed; // px/s
    bool is_smooth();
    bool is_striped();
    unsigned id;
    sf::CircleShape shape;
    float mass = 0.200; // 0.200 kg
    float frictionDeceleration; // Coefficiente di attrito
    sf::Time last = sf::Time::Zero;
};

#endif
