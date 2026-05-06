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
    sf::Vector2f my_pos = shape.getPosition();
    sf::Vector2f new_pos = my_pos + speed * time.asSeconds();

    std::vector<Collision> collisions = getFutureCollisions();

    if(!collisions.empty()){
        // Devo simulare ora la collisione o posso farlo al prossimo frame?
        std::vector<int> simulated_collisions;

        for(size_t index = 0; index < collisions.size(); index++){
            Collision c = collisions.at(index);
            if(dist(my_pos, c.position_at_collision) < dist(my_pos, new_pos)){ // Devo simulare ora la collisione
                sf::Vector2f n = c.collision_point - my_pos;
                n /= norm(n);
                sf::Vector2f vdelta = (c.collider_speed - speed);
                float velocity_relative_to_n = dot(n, vdelta); // Prodotto scalare
                float my_mass_opp = 1 / getMass();
                float collider_mass_opp = 1 / c.collider_mass;
                float impulse = (-2*velocity_relative_to_n) / (my_mass_opp + collider_mass_opp);
                speed += ( (impulse / getMass()) * n ); // Nuova velocità finale
                new_pos = my_pos + speed * time.asSeconds();
                simulated_collisions.push_back(index);
            }
        }
        for(size_t to_remove : simulated_collisions){
            std::cout << "Removing " << to_remove << std::endl;
            collisions.erase(collisions.begin() + to_remove);
        }

    }

    shape.setPosition(new_pos);


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
    std::vector<sf::Vector2f> res; //
    float angle = PI / 4.0f; // 45 gradi
    sf::Vector2f radiusVec = {0, -shape.getRadius()};// - Radius perchè le y sono invertite
    sf::Vector2f position = shape.getPosition();
    // Ruoto il vettore raggio parallelo all'asse y di 9 volte (cosi riprendo il punto finale)
    // per modellare la mia pallina come un ottagono
    for(int i = 0; i <= 8; i++){
        res.push_back(radiusVec + position);
        radiusVec = rotate(radiusVec, angle, true);
    }
    return res;
}

sf::FloatRect Ball::getBoundBox() const
{
    sf::Vector2f pos = shape.getPosition();
    float r = shape.getRadius();
    return sf::FloatRect({pos.x - r, pos.y - r}, {pos.x + r, pos.y + r});
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
    return "Ball[" + std::to_string(id) + "]";
}

