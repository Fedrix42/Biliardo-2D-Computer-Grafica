#ifndef HBWALKER_H
#define HBWALKER_H
#include <SFML/Graphics.hpp>

struct HitboxWalker {
    std::vector<sf::Vector2f> self_hitbox;
    std::vector<sf::Vector2f> collider_hitbox;
    size_t self_hb_size;
    size_t collider_hb_size;
    size_t i;
    size_t j;
    std::pair< sf::Vector2f, sf::Vector2f > self_segment();
    std::pair<sf::Vector2f, sf::Vector2f> collider_segment();
    bool hasNext() const;
    void step();
    static HitboxWalker getHitboxIterator(std::vector<sf::Vector2f> self_hitbox, std::vector<sf::Vector2f> collider_hitbox);
};

#endif
