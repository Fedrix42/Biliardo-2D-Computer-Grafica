#include "paddle.h"


Paddle::Paddle(sf::Vector2f start_pos){
    this->paint = sf::RectangleShape(size);
    this->texture = sf::Texture(DEFAULT_TEXTURE_PATH);
    this->pos = start_pos;
    this->paint.setTexture(&texture);
    this->paint.setOrigin({size.x / 2, size.y});
    this->paint.setPosition(this->pos);
}

void Paddle::draw(sf::RenderWindow& window){
    window.draw(this->paint);
}
