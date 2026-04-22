#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "assets.h"

class Ball {
public:
    const std::string DEFAULT_TEXTURE_PATH = TEXTURES_FOLDER + "texture_ball.png";
    float rspeed = 0.08; // Relative speed to the window height
    sf::Texture texture;
    float radius = 10.0;
    sf::Vector2f pos;
    sf::CircleShape paint;

    Ball(sf::Vector2f start_pos);
    ~Ball(); // Distruttore


    void draw(sf::RenderWindow& window);
    bool move(sf::RenderWindow& window); // False if the ball goes outside of the allowed space and its game over

};


#endif