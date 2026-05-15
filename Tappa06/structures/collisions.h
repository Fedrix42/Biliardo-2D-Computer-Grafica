#ifndef COLLIDER_H
#define COLLIDER_H
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
};

struct Collision {
    sf::Time collision_time;
    sf::Vector2f self_normal; // Perpendiolare e normalizzato al punto di impatto
    float self_velocity_along_normal;
    float collider_velocity_along_normal;
    sf::Vector2f collision_point; // Punto di collisione
    bool applied = false;
};

class Ball;
class TableWall;

bool doesBoundBoxesCollide(Ball* self, Ball* collider);
bool doesBoundBoxesCollide(Ball* self, TableWall* wall);
std::optional<std::pair<Collision, Collision>> computeCollision(Ball* self, Ball* collider, sf::Time current_t);
std::optional<Collision> computeCollision(Ball* self, TableWall* wall, sf::Time current_t);






#endif
