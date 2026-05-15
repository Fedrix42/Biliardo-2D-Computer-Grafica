#include "collisions.h"
#include "../utils.h"
#include <iostream>
#include "ball.h"
#include "table/tablewall.h"

HitboxWalker getHitboxIterator(std::vector<sf::Vector2f> self_hitbox, std::vector<sf::Vector2f> collider_hitbox){
    if (self_hitbox.empty() || collider_hitbox.empty()) {
        throw std::invalid_argument("Empty hitbox");
    }
    return HitboxWalker {
            self_hitbox,
            collider_hitbox,
            self_hitbox.size(),
            collider_hitbox.size(),
            0,
            0,
    };
}

bool HitboxWalker::hasNext() const{
    return i < self_hb_size;
}


void HitboxWalker::step(){
    if(!HitboxWalker::hasNext()){
        throw std::logic_error("Iteration has terminated.");
    }
    j++;
    if (j >= collider_hb_size)
    {
        j = 0;
        ++i;
    }
}

std::pair<sf::Vector2f, sf::Vector2f> HitboxWalker::self_segment(){
    return {self_hitbox.at(i), self_hitbox.at((i + 1) % self_hb_size)};
}

std::pair<sf::Vector2f, sf::Vector2f> HitboxWalker::collider_segment(){
    return {collider_hitbox.at(j), collider_hitbox.at((j + 1) % collider_hb_size)};
}


bool doesBoundBoxesCollide(Ball* self, Ball* collider){
    return self->getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

bool doesBoundBoxesCollide(Ball* self, TableWall* wall){
    return self->getBoundBox().findIntersection(wall->getBoundBox()) != std::nullopt;
}


std::optional<Collision> computeCollision(Ball* self, TableWall* wall, sf::Time current_t){
    sf::Vector2f self_old_pos = self->getPosition();
    float self_speed_module = norm(self->getSpeed());
    sf::Vector2f my_normalized_speed = (self_speed_module != 0) ? (self->getSpeed() / self_speed_module) : (sf::Vector2f{0, 0});
    float self_deceleration = self->getDecelleration();


    HitboxWalker walker;
    sf::Time simulation_t = sf::Time::Zero;
    sf::Time step = sf::seconds(0.001); // 1 ms
    sf::Time stop = sf::seconds(0.1); // Simulo 100 ms

    while(simulation_t < stop){
        walker = getHitboxIterator(self->getHitbox(), wall->getHitbox());
        // Controllo le hitbox correnti
        while(walker.hasNext()){
            auto self_seg = walker.self_segment();
            auto wall_seg = walker.collider_segment();
            auto collision_point = segment_intersection(self_seg.first, self_seg.second, wall_seg.first, wall_seg.second);
            if(collision_point){
                sf::Vector2f from_wall_to_ball = self->getPosition() - (*collision_point);
                sf::Vector2f wall_normal = clkwise_rot(wall_seg.first - wall_seg.second) / norm(wall_seg.first - wall_seg.second);
                if(dot(from_wall_to_ball, wall_normal) < 0.0f){
                    wall_normal = opposite(wall_normal);
                }
                self->setPosition(self_old_pos); // Rollback
                return Collision {
                    current_t + simulation_t,
                    wall_normal, // Mia normale
                    dot(wall_normal, speedAfterTime(self->getSpeed(), self_deceleration, simulation_t)),
                    0.0f, // Il muro è fermo
                    *collision_point
                };

            }
            walker.step();
        }

        simulation_t += step;
        float self_traveled = distanceOnTime(self_speed_module, self_deceleration, simulation_t);
        if(self_traveled < 0.000001f){
            break;
        }
        self->setPosition(self_old_pos + (self_traveled * my_normalized_speed));
    }
    // Rollback
    self->setPosition(self_old_pos);
    return std::nullopt;
}



std::optional<std::pair<Collision, Collision>> computeCollision(Ball* self, Ball* collider, sf::Time current_t){
    sf::Vector2f self_old_pos = self->getPosition();
    sf::Vector2f collider_old_pos = collider->getPosition();

    float self_speed_module = norm(self->getSpeed());
    float collider_speed_module = norm(collider->getSpeed());

    sf::Vector2f my_normalized_speed = (self_speed_module != 0) ? (self->getSpeed() / self_speed_module) : (sf::Vector2f{0, 0});
    sf::Vector2f collider_normalized_speed = (collider_speed_module != 0) ? (collider->getSpeed() / collider_speed_module) : (sf::Vector2f{0, 0});

    float self_deceleration = self->getDecelleration();
    float collider_deceleration = collider->getDecelleration();

    HitboxWalker walker;
    sf::Time simulation_t = sf::Time::Zero;
    sf::Time step = sf::seconds(0.001); // 1 ms
    sf::Time stop = sf::seconds(0.1); // Simulo 100 ms

    while(simulation_t < stop){
        walker = getHitboxIterator(self->getHitbox(), collider->getHitbox());
        // Controllo le hitbox correnti
        while(walker.hasNext()){
            auto self_seg = walker.self_segment();
            auto coll_seg = walker.collider_segment();
            auto collision_point = segment_intersection(self_seg.first, self_seg.second, coll_seg.first, coll_seg.second);
            if(collision_point){
                std::pair<Collision, Collision> result;
                sf::Vector2f self_normal = self->getPosition() - collider->getPosition();
                self_normal /= norm(self_normal);
                sf::Vector2f collider_normal = opposite(self_normal);
                sf::Vector2f relative_speed = self->getSpeed() - collider->getSpeed();

                // Rollback delle posizioni originale
                self->setPosition(self_old_pos);
                collider->setPosition(collider_old_pos);

                if(dot(relative_speed, self_normal) < 0.0f){ // Si stanno avvicinando
                    result.first = Collision {
                            current_t + simulation_t,
                            self_normal,
                            dot(self_normal, speedAfterTime(self->getSpeed(), self_deceleration, simulation_t)),
                            dot(collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t)),
                            *collision_point
                    };
                    result.second = Collision {
                            current_t + simulation_t,
                            collider_normal,
                            dot(collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t)),
                            dot(self_normal, speedAfterTime(self->getSpeed(), self_deceleration, simulation_t)),
                            *collision_point
                    };
                    return result;
                } else {
                    return std::nullopt;
                }

            }
            walker.step();
        }

        simulation_t += step;
        float self_traveled = distanceOnTime(self_speed_module, self_deceleration, simulation_t);
        float collider_traveled = distanceOnTime(collider_speed_module, collider_deceleration, simulation_t);
        if(self_traveled < 0.000001f && collider_traveled < 0.000001f){
            break;
        }
        self->setPosition(self_old_pos + (self_traveled * my_normalized_speed));
        collider->setPosition(collider_old_pos + (collider_traveled * collider_normalized_speed));
    }
    // Rollback
    self->setPosition(self_old_pos);
    collider->setPosition(collider_old_pos);
    return std::nullopt;
}
