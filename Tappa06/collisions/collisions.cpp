#include "collisions.h"
#include "../utils.h"
#include <iostream>
#include "../structures/ball.h"
#include "../structures/table/tablewall.h"
#include "hitbox_walker.h"

bool doesBoundBoxesCollide(Ball* self, Ball* collider){
    return self->getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

bool doesBoundBoxesCollide(Ball* self, TableWall* wall){
    return self->getBoundBox().findIntersection(wall->getBoundBox()) != std::nullopt;
}

std::vector<Ball*>  compute_collisions(sf::Time current_t, std::optional<Ball> cue_tip, std::vector<Ball*> balls, std::vector<TableWall*> walls){
    // Collisioni stecca - palline
    std::vector<Ball*> cue_hitted_balls;
    if(cue_tip){
        balls.push_back(&(*cue_tip));
    }

    // Collisioni palline - muri
    for(Ball* b : balls){
        for(TableWall* w : walls){
            //std::cout << std::boolalpha << doesBoundBoxesCollide(b, w) << std::endl;
            if(doesBoundBoxesCollide(b, w) && b->walls_collisions.find(w) == b->walls_collisions.end()){
                // std::cout << b->to_string() << std::endl;
                auto res = computeCollision(b, w, current_t);
                if(res){
                    b->walls_collisions[w] = (*res);
                }
            }
        }
    }
    // Collisioni palline - palline
    for(size_t i = 0; i < balls.size(); ++i){
        for(size_t j = i + 1; j < balls.size(); ++j){
            Ball* self = balls.at(i);
            Ball* collider = balls.at(j);
            auto self_collisions = self->balls_collisions;
            auto collider_collisions = collider->balls_collisions;
            if(doesBoundBoxesCollide(self, collider)
                && self_collisions.find(collider) == self_collisions.end()
                && collider_collisions.find(self) == collider_collisions.end()){
                    //std::cout << self->to_string() << " con " << collider->to_string() << std::endl;
                    auto res = computeCollision(self, collider, current_t);
                    if(res){
                        self->balls_collisions[collider] = (*res).first;
                        collider->balls_collisions[self] = (*res).second;
                        if(collider == &(*cue_tip)){
                            cue_hitted_balls.push_back(self);
                        }
                    }
            }
        }
    }


    return cue_hitted_balls;
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
        walker = HitboxWalker::getHitboxIterator(self->getHitbox(), wall->getHitbox());
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
                    0.0f // Il muro è fermo
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


    sf::Time simulation_t = sf::Time::Zero;
    sf::Time step = sf::seconds(0.001); // 1 ms
    sf::Time stop = sf::seconds(0.1); // Simulo 100 ms

    while(simulation_t < stop){
        if(dist(self->getPosition(), collider->getPosition()) <= (self->getRadius() + collider->getRadius())){ // C'è una collisione
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
                        dot(collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t))
                };
                result.second = Collision {
                        current_t + simulation_t,
                        collider_normal,
                        dot(collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t)),
                        dot(self_normal, speedAfterTime(self->getSpeed(), self_deceleration, simulation_t))
                };
                return result;
            } else {
                return std::nullopt;
            }

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
