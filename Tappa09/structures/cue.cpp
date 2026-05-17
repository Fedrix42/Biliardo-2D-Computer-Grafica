#include "cue.h"
#include "../assetmgr.h"
#include "../utils.h"
#include <iostream>
#include <cmath>


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
    tip.setPosition(body.getTransform().transformPoint(local_tip));
    body.setTexture(AssetMGR::instance().cue_texture());
    direction = {0, -1};
}

void Cue::update(const sf::Event::MouseMoved* moved){
    if(shooting || !enabled) return;
    sf::Vector2f mouse = {static_cast<float>(moved->position.x), static_cast<float>(moved->position.y)};
    switch(type){
        case CueType::FREE:
            body.setPosition(mouse);
            tip.setPosition(body.getTransform().transformPoint(local_tip));
            break;
        case CueType::ANCHOR:
            sf::Vector2f anchorpos = anchor->getPosition();
            sf::Vector2f fromto = anchorpos - mouse;
            float n = norm(fromto);
            if(n < anchor->getRadius()){ // Il cursore è dentro la pallina
                return;
            }
            direction = fromto / n;
            sf::Vector2f opp_direction = opposite(direction);

            tip.setPosition(opp_direction * anchor->getRadius() + opp_direction * (tip.getRadius() * 0.8f));
            // ^ Moltiplico per 0.8f per avere una conpenetrazione tra la tip e l'anchor
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
}

void Cue::shot(float speed)
{
    this->speed = speed;
    shooting = true;
}

std::optional<Ball> Cue::advance(sf::Time current_t)
{
    /*
        Animazione del colpo e materializzazione della pallina per le collisioni nell'ultimo istante dell'animazione
        L'animazione deve far andare indietro la stecca per 1 secondo e poi farla tornare avanti
    */
    if(enabled && shooting){
        if(shot_start_animation == sf::Time::Zero){
            shot_start_animation = current_t;
        }
        sf::Time delta = current_t - last;
        auto travel = direction * (animation_backward_speed * delta.asSeconds());
        if(current_t - shot_start_animation >= sf::seconds(0.3f)){
            if(backward){ // Ora devo andare avanti
                backward = false;
                shot_start_animation = current_t;
            } else {
                // Animazione terminata
                Ball materialized = Ball(99, tip.getRadius(), 1, tip.getPosition());
                materialized.setSpeed(direction * speed); // La vera velocità del colpo (Non quella animazione)
                shooting = false;
                backward = true;
                shot_start_animation = sf::Time::Zero;
                return materialized;
            }
        }
        if(backward){
            travel = opposite(travel);
        }
        body.setPosition(body.getPosition() + travel);
        tip.setPosition(tip.getPosition() + travel);
    }
    last = current_t;
    return std::nullopt;
}


void Cue::rotate(bool clockwise)
{
    if(enabled && type == CueType::FREE){
        sf::Angle angle = (clockwise) ? sf::degrees(ROTATION_ANGLE_DEGREE) : sf::degrees(-ROTATION_ANGLE_DEGREE);
        body.rotate(angle); // sin cos scambiati perchè il rettangolo è in verticale
        tip.setPosition(body.getTransform().transformPoint(local_tip));
        direction = (tip.getPosition() - body.getPosition()) / norm((tip.getPosition() - body.getPosition()));
    }
}


void Cue::draw(sf::RenderWindow& window)
{
    if(enabled){
        window.draw(body);
        window.draw(tip);
    }
}

bool Cue::isShooting()
{
    return shooting;
}


