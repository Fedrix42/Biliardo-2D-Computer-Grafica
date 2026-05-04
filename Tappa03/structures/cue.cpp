#include "cue.h"
#include "../assetmgr.h"
#include "../utils.h"
#include <iostream>

const float HALF_CUE_WIDTH = 2;

Cue::Cue()
{
    shape.setFillColor(sf::Color::Black);
    shape.setPointCount(4);
    //shape.setTexture(AssetMGR::instance()....);
}

void Cue::update_position(const sf::Event::MouseMoved* moved){
    sf::Vector2f mouse = {static_cast<float>(moved->position.x), static_cast<float>(moved->position.y)};
    sf::Vector2f anchorpos = anchor->getPosition();
    sf::Vector2f fromto = anchorpos - mouse;
    float n = norm(fromto);
    if(n < anchor->getRadius()){ // Il cursore è dentro la pallina
        return;
    }

    speed = n;
    fromto = fromto / n;
    direction = fromto;
    impact = (opposite(fromto) * anchor->getRadius() + anchorpos);

    shape.setPoint(0, ((clkwise_rot(fromto) * HALF_CUE_WIDTH) + mouse));
    shape.setPoint(1, ((counterclkwise_rot(fromto) * HALF_CUE_WIDTH) + mouse));
    shape.setPoint(2, ((counterclkwise_rot(fromto) * HALF_CUE_WIDTH) + impact));
    shape.setPoint(3, ((clkwise_rot(fromto) * HALF_CUE_WIDTH) + impact));
}

float Cue::getSpeed()
{
    return speed;
}


void Cue::setHide(bool h){
    hide = h;
}

void Cue::draw(sf::RenderWindow& window)
{
    if(hide){
        window.draw(shape);
    }
}

sf::Vector2f Cue::getDirection()
{
    return direction;
}


void Cue::setAnchor(Ball* anchor){
    if(anchor == nullptr)
        throw std::invalid_argument("Nullptr arg");
    this->anchor = anchor;
}

Ball* Cue::getAnchor()
{
    return anchor;
}


float Cue::getMass()
{
    return weight;
}

