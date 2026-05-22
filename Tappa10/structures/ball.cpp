#include "ball.h"
#include "../assetmgr.h"
#include <iostream>
#include "../utils.h"

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
Palline da 6cm, quindi in proporzione la metà di una buca
*/

Ball::Ball(unsigned int id, float pocket_radius, float tableFrictionCoeff, sf::Vector2f pos)
{
    this->id = id;
    float r = pocket_radius / 2;
    shape.setRadius(r);
    shape.setOrigin({r, r});
    shape.setPosition(pos);
    if(id >= BallIDRange::TOTAL_START && id <= BallIDRange::TOTAL_STOP ){ // ID negativo rappresenta pallina virtuali (Come la punta della stecca)
        shape.setTexture(AssetMGR::instance().get_ball_texture(id));
    }
    friction_deceleration = tableFrictionCoeff; // Ipotizzo il coefficiente di attrito sia uguale per tutte le palline e sia quello del tavolo
}

void Ball::resize(sf::Vector2f factors, float new_pocket_radius, sf::Vector2f new_offset, sf::Vector2f old_offset)
{

    //std::cout << point_to_str(new_offset) << " -- " << point_to_str(factors) << std::endl;
    float r = new_pocket_radius / 2;
    shape.setRadius(r);
    shape.setOrigin({r, r});
    auto rel_pos = shape.getPosition() - old_offset;
    rel_pos.x *= factors.x;
    rel_pos.y *= factors.y;
    shape.setPosition(new_offset + rel_pos);
}


float Ball::get_radius()
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
    speed = utils::physics::speedAfterTime(speed, friction_deceleration, delta);


    sf::Vector2f my_pos = get_position();
    sf::Vector2f next_pos = my_pos;

    // Collisioni con muri
    std::vector<TableWall*> walls_to_clear;
    for(auto &entry : walls_collisions){
        TableWall* wall = entry.first;
        Collision& c = entry.second;

        if(!c.applied && current_t >= c.collision_time){ // Devo simulare ora la collisione
            // Metodo dell'impulso
            sf::Vector2f unitary_normal_vector = c.self_normal;
            float my_start_velocity_alongn = c.self_velocity_along_normal;
            speed -= 2.f * unitary_normal_vector * my_start_velocity_alongn;
            next_pos += speed * delta.asSeconds();
            c.applied = true;
            walls_to_clear.push_back(wall);
        }
    }
    for(TableWall* w : walls_to_clear){
        walls_collisions.erase(w);
    }

    // Collisioni con palline
    std::vector<Ball*> balls_to_clear;
    for(auto entry : balls_collisions){
        Ball* collider_ball = entry.first;
        Collision& c = entry.second;

        if(!c.applied && current_t >= c.collision_time){ // Devo simulare ora la collisione
            // Metodo dell'impulso
            sf::Vector2f unitary_normal_vector = c.self_normal;

            // Componenti delle velocità normalizzate rispetto la linea di impatto
            float my_start_velocity_alongn = c.self_velocity_along_normal;
            float against_start_velocity_alongn = c.collider_velocity_along_normal;

            // Calcolo la componente finale lungo la linea di impatto
            float my_final_velocity_alongn = utils::monocollisions::finalSpeed1D_ofA(get_mass(), collider_ball->get_mass(), my_start_velocity_alongn, against_start_velocity_alongn);
            float my_delta_velocity_alongn = fabsf(my_final_velocity_alongn - my_start_velocity_alongn);
            my_delta_velocity_alongn = (my_delta_velocity_alongn < 0.0001f) ? 0.0f : my_delta_velocity_alongn;
            /* std::cout << to_string()
                << "\n\t UVN: " << point_to_str(unitary_normal_vector)
                << "\n\t Vel. iniziale ln: " << my_start_velocity_alongn
                << "\n\t Vel. iniziale against ln: " << against_start_velocity_alongn
                << "\n\t Vel. finale ln: " << my_final_velocity_alongn
                << "\n\t Vel. delta ln: " << my_delta_velocity_alongn << std::endl;
            */
            speed += unitary_normal_vector*my_delta_velocity_alongn;

            c.applied = true;
            balls_to_clear.push_back(collider_ball);
        }
    }

    for(Ball* b : balls_to_clear){
        balls_collisions.erase(b);
    }


    if(walls_to_clear.empty() && balls_to_clear.empty()){ // Nessuna collisione, classica formula della velocità
        next_pos = my_pos + speed * delta.asSeconds();
    }
    shape.setPosition(next_pos);
    last = current_t;

}

float Ball::get_decelleration() const
{
    return friction_deceleration;
}


void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

float Ball::get_mass() const
{
    return mass;
}

std::vector<sf::Vector2f> Ball::get_hitbox() const {
    const int sides = 8;
    std::vector<sf::Vector2f> res;
    float angle = 2.0f * PI / static_cast<float>(sides);
    sf::Vector2f radius_vec = {0, -shape.getRadius()};
    sf::Vector2f position = get_position();

    for (int i = 0; i < sides; i++) {
        res.push_back(radius_vec + position);
        radius_vec = utils::vectors_screen_space::rotate(radius_vec, angle, true);
    }

    return res;
}

sf::FloatRect Ball::get_bound_box() const
{
    sf::Vector2f pos = get_position();
    float r = shape.getRadius();
    r = r * 1.5f; // Aumento il raggio per fare una bounding box più grande ed identificare meglio gli urti a grandi velocità
    return sf::FloatRect({pos.x - r, pos.y - r}, {2*r, 2*r});
}


sf::Vector2f Ball::get_position() const {
    return shape.getPosition();
}

sf::Vector2f Ball::get_speed() const
{
    return speed;
}

void Ball::set_position(sf::Vector2f pos){
    shape.setPosition(pos);
}

void Ball::set_speed(sf::Vector2f speed){
    this->speed = speed;
}

std::string Ball::to_string() const {
    return ("Ball["  + std::to_string(id) + " -- "
                     + utils::point_to_str(get_bound_box().position)
                     + utils::point_to_str(get_bound_box().size)
    + "]");
}

unsigned int Ball::get_id()
{
    return id;
}

void Ball::set_mass(float mass)
{
    this->mass = mass;
}


