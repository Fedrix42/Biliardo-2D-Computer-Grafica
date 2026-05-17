#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "../collisions/collisions.h"

enum BallIDRange {
    SMOOTH_START = 1,
    SMOOTH_STOP = 7,
    BLACK = 8,
    STRIPED_START = 9,
    STRIPED_STOP = 15,
    WHITE = 16,
    TOTAL_START = 1,
    TOTAL_STOP = 16
};

class Ball {
public:
    Ball(unsigned id, float pocket_radius, float tableFrictionCoeff, sf::Vector2f pos);
    Ball() = default;
    void draw(sf::RenderWindow& window);
    void update(sf::Time current_t);
    float getRadius();
    void resize(sf::Vector2f factors, float new_pocket_radius, sf::Vector2f new_offset, sf::Vector2f old_offset);
    float getMass() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSpeed() const;
    void setPosition(sf::Vector2f pos);
    void setSpeed(sf::Vector2f speed);
    std::string to_string() const;
    float getDecelleration() const;
    std::vector<sf::Vector2f> getHitbox() const;
    sf::FloatRect getBoundBox() const;
    std::unordered_map<Ball*, Collision> balls_collisions;
    std::unordered_map<TableWall*, Collision> walls_collisions;
    unsigned getID();
    bool is_smooth();
    bool is_striped();
private:
    sf::Vector2f speed; // px/s
    unsigned id;
    sf::CircleShape shape;
    float mass = 0.200; // 0.200 kg
    float frictionDeceleration; // Coefficiente di attrito
    sf::Time last = sf::Time::Zero;
};

#endif
