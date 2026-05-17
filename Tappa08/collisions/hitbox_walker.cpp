#include "hitbox_walker.h"


HitboxWalker HitboxWalker::getHitboxIterator(std::vector<sf::Vector2f> self_hitbox, std::vector<sf::Vector2f> collider_hitbox){
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
