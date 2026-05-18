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
    float get_radius();
    void resize(sf::Vector2f factors, float new_pocket_radius, sf::Vector2f new_offset, sf::Vector2f old_offset);
    float get_mass() const;
    void set_mass(float mass);
    sf::Vector2f get_position() const;
    sf::Vector2f get_speed() const;
    void set_position(sf::Vector2f pos);
    void set_speed(sf::Vector2f speed);
    std::string to_string() const;
    float get_decelleration() const;
    std::vector<sf::Vector2f> get_hitbox() const;
    sf::FloatRect get_bound_box() const;
    std::unordered_map<Ball*, Collision> balls_collisions;
    std::unordered_map<TableWall*, Collision> walls_collisions;
    unsigned get_id();
    bool is_smooth();
    bool is_striped();
    constexpr static const float DEFAULT_MASS = 0.2f;// 0.200 kg
private:
    sf::Vector2f speed; // px/s
    unsigned id;
    sf::CircleShape shape;
    float mass = DEFAULT_MASS;
    float friction_deceleration; // Coefficiente di attrito
    sf::Time last = sf::Time::Zero;
};

#endif
