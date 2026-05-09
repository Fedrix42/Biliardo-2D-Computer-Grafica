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
    frictionDeceleration = tableFrictionCoeff; // Ipotizzo il coefficiente di attrito sia uguale per tutte le palline e sia quello del tavolo
}

float Ball::getRadius()
{
    return shape.getRadius();
}

bool Ball::is_smooth(){
    return (id >= BallIDRange::SMOOTH_START && id <= BallIDRange::SMOOTH_STOP);
}

bool Ball::is_striped(){
    return (id >= BallIDRange::STRIPED_START && id <= BallIDRange::STRIPED_STOP);
}


void Ball::update(sf::Time current_t){
    sf::Time delta = current_t - last;
    // Decellerazione
    float speed_module = norm(speed);
    if(speed_module > 0){ // Altrimenti è ferma
        sf::Vector2f speed_norm = speed / speed_module;
        float deceleration = frictionDeceleration * delta.asSeconds();
        if(deceleration >= speed_module){
            speed = {0,0};
        } else {
            speed -= speed_norm * deceleration;
        }
    }

    // Calcolo nuova posizione
    sf::Vector2f my_pos = getPosition();
    sf::Vector2f next_pos = my_pos;

    if(!collisions.empty()) {
        for(auto &entry : collisions){
            Collider* against = entry.first; // L'oggetto contro cui collido
            Collision& c = entry.second;

            //std::cout << dist(my_pos, c.collision_point) << " " << getRadius() << std::endl;
            if(!c.applied && current_t >= c.collision_time){ // Devo simulare ora la collisione
                // Metodo dell'impulso
                sf::Vector2f unitary_normal_vector = c.normal;

                // Componenti delle velocità normalizzate rispetto la linea di impatto
                float my_start_velocity_alongn = this->velocityAlongNormal(against);
                float against_start_velocity_alongn = against->velocityAlongNormal(this);

                // Calcolo la componente finale lungo la linea di impatto
                float my_final_velocity_alongn = fnspeedA_1D(getMass(), against->getMass(), my_start_velocity_alongn, against_start_velocity_alongn);
                float my_delta_velocity_alongn = my_final_velocity_alongn - my_start_velocity_alongn;

                speed += unitary_normal_vector*my_delta_velocity_alongn; // La vera velocità finale


                std::cout << "[BALL] Risultato della collisione bidimensionale:"
                    << "\n\tPunto di impatto: " << point_to_str(c.collision_point)
                    << "\n\tVettore normale unitario: " << point_to_str(unitary_normal_vector)
                    << "\n\tVelocità lungo la normale: " << my_start_velocity_alongn
                    << "\n\tVelocità del collisore lungo la normale: " << against_start_velocity_alongn
                    << "\n\tVelocità finale lungo la normale: " << my_final_velocity_alongn
                    << "\n\tDifferenza di velocità lungo la normale: " << my_delta_velocity_alongn
                    << "\n\tVelocità finale: " << point_to_str(speed)
                    << std::endl;


                next_pos += speed * delta.asSeconds();
                c.applied = true;
            }
        }
    }
    if(next_pos == my_pos){ // Nessuna collisione
        next_pos = my_pos + speed * delta.asSeconds();
    }
    shape.setPosition(next_pos);
    last = current_t;
}

float Ball::getDecelleration() const
{
    return frictionDeceleration;
}


void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

float Ball::getMass() const
{
    return mass;
}



std::vector<sf::Vector2f> Ball::getHitbox() const {
    const int sides = 16;
    std::vector<sf::Vector2f> res;
    float angle = 2.0f * PI / static_cast<float>(sides);
    sf::Vector2f radius_vec = {0, -shape.getRadius()};
    sf::Vector2f position = shape.getPosition();

    for (int i = 0; i < sides; i++) {
        res.push_back(radius_vec + position);
        radius_vec = rotate(radius_vec, angle, true);
    }

    return res;
}

sf::FloatRect Ball::getBoundBox() const
{
    sf::Vector2f pos = shape.getPosition();
    float r = shape.getRadius();
    r = 2*r; // Raddoppio il raggio per fare una bounding box molto più grande ed identificare meglio gli urti a grandi velocità
    return sf::FloatRect({pos.x - r, pos.y - r}, {2*r, 2*r});
}


sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Ball::getSpeed() const
{
    return speed;
}

void Ball::setPosition(sf::Vector2f pos){
    shape.setPosition(pos);
}

void Ball::setSpeed(sf::Vector2f speed){
    this->speed = speed;
}

std::string Ball::to_string() const {
    return ("Ball["  + std::to_string(id) + " -- "
                     + point_to_str(getBoundBox().position)
                     + point_to_str(getBoundBox().size)
    + "]");
}

