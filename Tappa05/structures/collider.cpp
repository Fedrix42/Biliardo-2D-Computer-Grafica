#include "collider.h"
#include "../utils.h"
#include <iostream>

void rollbackPositions(Collider* c1, Collider* c2, sf::Vector2f c1p, sf::Vector2f c2p){
    c1->setPosition(c1p);
    c2->setPosition(c2p);
}

std::optional<IntersectionResult> Collider::checkSegmentIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D) const {
    std::optional<sf::Vector2f> impact_point = segment_intersection(A, B, C, D);

    if(impact_point){
        sf::Vector2f my_segment = B - A;
        sf::Vector2f collider_segment = D - C;
        sf::Vector2f my_normal = clkwise_rot(my_segment) / norm(my_segment); // Perpendiolare al segmento B - A
        sf::Vector2f collider_normal = counterclkwise_rot(collider_segment) / norm(collider_segment);

        return IntersectionResult{ // Aggiungi la collisione a me
            my_normal,
            collider_normal,
            *impact_point
        };
    }else {
        return std::nullopt;
    }

}


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

bool HitboxWalker::hasNext() const
{
    return i < self_hb_size;
}


void HitboxWalker::step()
{
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

std::pair<sf::Vector2f, sf::Vector2f> HitboxWalker::self_segment()
{
    return {self_hitbox.at(i), self_hitbox.at((i + 1) % self_hb_size)};
}

std::pair<sf::Vector2f, sf::Vector2f> HitboxWalker::collider_segment()
{
    return {collider_hitbox.at(j), collider_hitbox.at((j + 1) % collider_hb_size)};
}


std::vector<sf::Vector2f> getSegmentIterator();

std::optional<std::pair<Collision, Collision>> Collider::computeCollisions(Collider* collider, sf::Time current_t)
{
    sf::Vector2f self_old_pos = getPosition();
    sf::Vector2f collider_old_pos = collider->getPosition();

    float self_speed_module = norm(getSpeed());
    float collider_speed_module = norm(collider->getSpeed());

    sf::Vector2f my_normalized_speed = (self_speed_module != 0) ? (getSpeed() / self_speed_module) : (sf::Vector2f{0, 0});
    sf::Vector2f collider_normalized_speed = (collider_speed_module != 0) ? (collider->getSpeed() / collider_speed_module) : (sf::Vector2f{0, 0});

    float self_deceleration = getDecelleration();
    float collider_deceleration = collider->getDecelleration();

    HitboxWalker walker;
    sf::Time simulation_t = sf::Time::Zero;
    sf::Time step = sf::seconds(0.001); // 1 ms
    sf::Time stop = sf::seconds(0.1); // Simulo 100 ms

    while(simulation_t < stop){
        walker = getHitboxIterator(getHitbox(), collider->getHitbox());
        // Controllo le hitbox correnti
        while(walker.hasNext()){
            auto self_seg = walker.self_segment();
            auto coll_seg = walker.collider_segment();
            auto intersection_res = checkSegmentIntersection(self_seg.first, self_seg.second, coll_seg.first, coll_seg.second);
            if(intersection_res){
                std::pair<Collision, Collision> result;
                result.first = Collision {
                        current_t + simulation_t,
                        (*intersection_res).self_normal,
                        dot((*intersection_res).self_normal, speedAfterTime(getSpeed(), self_deceleration, simulation_t)),
                        dot((*intersection_res).collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t)),
                        (*intersection_res).collision_point
                };
                result.second = Collision {
                        current_t + simulation_t,
                        (*intersection_res).collider_normal,
                        dot((*intersection_res).collider_normal, speedAfterTime(collider->getSpeed(), collider_deceleration, simulation_t)),
                        dot((*intersection_res).self_normal, speedAfterTime(getSpeed(), self_deceleration, simulation_t)),
                        (*intersection_res).collision_point
                };
                rollbackPositions(this, collider, self_old_pos, collider_old_pos);
                return result;
            }
            walker.step();
        }

        simulation_t += step;
        float self_traveled = distanceOnTime(self_speed_module, self_deceleration, simulation_t);
        float collider_traveled = distanceOnTime(collider_speed_module, collider_deceleration, simulation_t);
        if(self_traveled < 0.000001f && collider_traveled < 0.000001f){
            break;
        }
        setPosition(self_old_pos + (self_traveled * my_normalized_speed));
        collider->setPosition(collider_old_pos + (collider_traveled * collider_normalized_speed));
    }
    rollbackPositions(this, collider, self_old_pos, collider_old_pos); // Importante: devo fare il rollback delle posizioni originali
    return std::nullopt;
}


bool Collider::doesBoundBoxesCollide(Collider* collider)
{
    return getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

