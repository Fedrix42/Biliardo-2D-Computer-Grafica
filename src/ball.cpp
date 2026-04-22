#include "ball.h"

Ball::Ball(sf::Vector2f start_pos){
    this->paint = sf::CircleShape(radius);
    this->texture = sf::Texture(DEFAULT_TEXTURE_PATH);
    this->paint.setTexture(&texture);
    this->paint.setOrigin({radius, radius});
    this->pos = start_pos;
    this->paint.setPosition(this->pos);
}

void Ball::draw(sf::RenderWindow& window){
    window.draw(this->paint);
}

bool Ball::move(sf::RenderWindow& window){
    if(pos.y < radius || pos.y > window.getSize().y - radius){
        rspeed = rspeed * (-1);
    }
    pos = {pos.x, pos.y - rspeed};
}