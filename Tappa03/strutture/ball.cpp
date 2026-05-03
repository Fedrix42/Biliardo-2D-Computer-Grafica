#include "ball.h"
#include "../assetmgr.h"
#include <iostream>

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
Palline da 6cm, quindi in proporzione la metà di una buca
*/

Ball::Ball(unsigned id, float pocket_radius)
{
    this->id = id;
    float r = pocket_radius / 2;
    shape.setRadius(r);
    shape.setOrigin({r, r});
    shape.setPosition({100 + 20*static_cast<float>(id), 100});
    shape.setTexture(AssetMGR::instance().get_ball_texture(id));
}
float Ball::getRadius()
{
    return shape.getRadius();
}


sf::Vector2f Ball::getPosition(){
    return shape.getPosition();
}

bool Ball::is_smooth(){
    return (id >= BallIDRange::SMOOTH_START && id <= BallIDRange::SMOOTH_STOP);
}

bool Ball::is_striped(){
    return (id >= BallIDRange::STRIPED_START && id <= BallIDRange::STRIPED_STOP);
}

void Ball::update(sf::Time time){
    shape.setPosition(shape.getPosition() + speed * time.asSeconds());
    //speed = speed / 10.0f; // Decellerazione costante (temporanea)
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

float Ball::getMass()
{
    return weight;
}
