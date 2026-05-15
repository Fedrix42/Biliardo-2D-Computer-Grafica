#include "cue.h"
#include "../assetmgr.h"
#include "../utils.h"
#include <iostream>

const float CUE_WIDTH = 8;
const float BODY_HEIGHT = 500;

Cue::Cue(sf::Vector2f position)
{
    tip.setFillColor(sf::Color::Black);
    body.setSize({
        CUE_WIDTH,
        BODY_HEIGHT
    });
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position); // Offset è la posizione del tavolo
    tip.setRadius(body.getSize().x / 2.0f);
    tip.setOrigin({tip.getRadius(), tip.getRadius()});
    tip.setPosition({body.getPosition().x, body.getPosition().y * 2.0f});
    body.setTexture(AssetMGR::instance().cue_texture());
}

void Cue::update(const sf::Event::MouseMoved* moved){
    sf::Vector2f mouse = {static_cast<float>(moved->position.x), static_cast<float>(moved->position.y)};
    switch(type){
        case CueType::FREE:
            body.setPosition(mouse);
            tip.setPosition({body.getPosition().x, body.getPosition().y - (body.getSize().y / 2.0f)});
            break;
        case CueType::ANCHOR:
            sf::Vector2f anchorpos = anchor->getPosition();
            sf::Vector2f fromto = anchorpos - mouse;
            float n = norm(fromto);
            if(n < anchor->getRadius()){ // Il cursore è dentro la pallina
                return;
            }
            sf::Vector2f opp_direction = opposite(fromto / n);
            tip.setPosition(opp_direction * anchor->getRadius() + opp_direction * tip.getRadius());
            tip.setPosition(tip.getPosition() + anchorpos);

            float bodyLength = body.getSize().y;
            body.setPosition(
                tip.getPosition() +
                opp_direction * (bodyLength / 2.f)
            );

            body.setRotation(
                sf::radians(std::atan2(opp_direction.y, opp_direction.x)) + sf::degrees(-90.f) // Aggiungo 90 perchè la stecca è in verticale
            );
            break;
    }
    /*

    sf::Vector2f anchorpos = anchor->getPosition();
    sf::Vector2f fromto = anchorpos - mouse;
    float n = norm(fromto);
    if(n < anchor->getRadius()){ // Il cursore è dentro la pallina
        return;
    }

    fromto = fromto / n;
    direction = fromto;
    impact = ((opposite(fromto) * anchor->getRadius()) + anchorpos);

    shape.setPoint(0, ((clkwise_rot(fromto) * (2 * HALF_CUE_WIDTH)) + mouse));
    shape.setPoint(1, ((counterclkwise_rot(fromto) * ( 2 * HALF_CUE_WIDTH)) + mouse));
    shape.setPoint(2, ((counterclkwise_rot(fromto) * HALF_CUE_WIDTH) + impact));
    shape.setPoint(3, ((clkwise_rot(fromto) * HALF_CUE_WIDTH) + impact));
    */
}



void Cue::draw(sf::RenderWindow& window)
{
    if(hide){
        window.draw(body);
        window.draw(tip);
    }
}

