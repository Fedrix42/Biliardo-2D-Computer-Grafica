#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
#include "assets.h"

class Paddle {
public:
    const std::string DEFAULT_TEXTURE_PATH = TEXTURES_FOLDER + "texture_paddle.png";
    float rspeed = 0.05; // Relative speed to the window height
    sf::Texture texture;
    sf::Vector2f size = {100.0, 16.0};
    sf::Vector2f pos;
    sf::RectangleShape paint;

    
    Paddle(sf::Vector2f start_pos);
    void draw(sf::RenderWindow& window);
};


#endif