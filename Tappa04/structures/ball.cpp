#include "ball.h"
#include "../assetmgr.h"
#include <iostream>
#include "../utils.h"
/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
Palline da 6cm, quindi in proporzione la metà di una buca
*/

Ball::Ball(unsigned id, float pocket_radius, float tableFrictionCoeff)
{
    this->id = id;
    float r = pocket_radius / 2;
    shape.setRadius(r);
    shape.setOrigin({r, r});
    shape.setPosition({100 + 20*static_cast<float>(id), 100});
    shape.setTexture(AssetMGR::instance().get_ball_texture(id));
    frictionCoeff = tableFrictionCoeff; // Ipotizzo il coefficiente di attrito sia uguale per tutte le palline e sia quello del tavolo
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
    // Decellerazione divisa per componente
    float decelleration = frictionCoeff * gravityCoefficient;
    if(speed.x > 0){
        speed.x -= decelleration * time.asSeconds();
        speed.x = (speed.x < 0.005f) ? 0 : speed.x; // Fermo la pallina quando va molto lenta
    }
    if(speed.y > 0){
        speed.y -= decelleration * time.asSeconds();
        speed.y = (speed.y < 0.005f) ? 0 : speed.y;
    }

    // Aggiornamento della posizione
    shape.setPosition(shape.getPosition() + speed * time.asSeconds());
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

float Ball::getMass()
{
    return weight;
}
