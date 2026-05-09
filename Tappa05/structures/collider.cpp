#include "collider.h"
#include "../utils.h"
#include <iostream>

void rollbackPositions(Collider* c1, Collider* c2, sf::Vector2f c1p, sf::Vector2f c2p){
    c1->setPosition(c1p);
    c2->setPosition(c2p);
}

std::optional<std::pair<Collision, Collision>> Collider::checkSegmentIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D) const {
    std::optional<sf::Vector2f> impact_point = segment_intersection(A, B, C, D);

    if(impact_point){
        sf::Vector2f my_segment = B - A;
        sf::Vector2f collider_segment = D - C;
        sf::Vector2f my_normal = clkwise_rot(my_segment) / norm(my_segment); // Perpendiolare al segmento B - A
        sf::Vector2f collider_normal = clkwise_rot(collider_segment) / norm(collider_segment);

        std::pair<Collision, Collision> result;
        result.first = Collision{ // Aggiungi la collisione a me
            sf::Time::Zero,
            my_normal,
            *impact_point
        };
        result.second = Collision{ // Aggiungi la collisione al collider
            sf::Time::Zero,
            collider_normal,
            *impact_point
        };
        return result;
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
            auto intersection = checkSegmentIntersection(self_seg.first, self_seg.second, coll_seg.first, coll_seg.second);
            if(intersection){
                (*intersection).first.collision_time = current_t + simulation_t;
                (*intersection).second.collision_time = current_t + simulation_t;
                rollbackPositions(this, collider, self_old_pos, collider_old_pos);
                return intersection;
            }
            walker.step();
        }

        simulation_t += step;
        float self_traveled = distanceOnTime(self_speed_module, self_deceleration, simulation_t);
        float collider_traveled = distanceOnTime(collider_speed_module, collider_deceleration, simulation_t);
        if(self_traveled < 0.005f && collider_traveled < 0.0005f){
            break;
        }
        setPosition(self_old_pos + (self_traveled * my_normalized_speed));
        collider->setPosition(collider_old_pos + (collider_traveled * collider_normalized_speed));
    }
    rollbackPositions(this, collider, self_old_pos, collider_old_pos); // Importante: devo fare il rollback delle posizioni originali
    return std::nullopt;
}



float Collider::velocityAlongNormal(Collider* collider) const
{
    auto it = collisions.find(collider);
    if(it != collisions.end()){
        return dot(getSpeed(), it->second.normal);
    }else {
        throw std::logic_error("[ERROR] No collision with collider");
    }

}


bool Collider::doesBoundBoxesCollide(Collider* collider)
{
    return getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

