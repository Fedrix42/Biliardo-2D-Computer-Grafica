#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <vector>

/*
Ball ID:
| 1 - 7 Smooth
| 8 Black
| 9 - 15 Striped
| 16 White
*/
enum BallIDRange {
    SMOOTH_START = 1,
    SMOOTH_STOP = 7,
    BLACK = 8,
    STRIPED_START = 9,
    STRIPED_STOP = 15,
    WHITE = 16
};

class Ball {
public:
    Ball(unsigned id, float pocket_radius);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void update(sf::Time time);
    float getRadius();
    float getMass();
    sf::Vector2f speed; // px/s
private:
    bool is_smooth();
    bool is_striped();
    unsigned id;
    sf::CircleShape shape;
    double weight = 0.200; // 0.200 kg
};

#endif
