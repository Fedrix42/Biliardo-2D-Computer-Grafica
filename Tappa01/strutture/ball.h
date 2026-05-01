#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <vector>

class BallView {
public:
    BallView();
    ~BallView() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    sf::CircleShape shape;
    sf::Texture texture; // Sarà basato sull'id della pallina
};

/*
Ball ID:
| 1 - 7 Smooth
| 8 Black
| 9 - 15 Striped
| 16 White
*/
enum BallID {
    SMOOTH_START = 1,
    SMOOTH_STOP = 7,
    BLACK = 8,
    STRIPED_START = 9,
    STRIPED_STOP = 15,
    WHITE = 16
};

class Ball {
public:
    Ball() = default;
    Ball(unsigned id);
    ~Ball() = default;
    void draw(sf::RenderWindow& window);

private:
    void compute_position();
    unsigned id;
    BallView view;
    double weight = 0.200; // 0.200 kg
    sf::Vector2f speed; // m/s
};

#endif