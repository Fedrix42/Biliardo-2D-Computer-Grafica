#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

struct Collision {
    sf::Time collision_time;
    sf::Vector2f self_normal; // Perpendiolare e normalizzato al punto di impatto
    float self_velocity_along_normal;
    float collider_velocity_along_normal;
    bool applied = false;
};

class Ball;
class TableWall;

bool doesBoundBoxesCollide(Ball* self, Ball* collider);
bool doesBoundBoxesCollide(Ball* self, TableWall* wall);
std::optional<std::pair<Collision, Collision>> computeCollision(Ball* self, Ball* collider, sf::Time current_t);
std::optional<Collision> computeCollision(Ball* self, TableWall* wall, sf::Time current_t);
/* Restituisce il vettore delle palline colpite dalla stecca (Nel caso di un colpo di stecca) */
std::vector<Ball*>  compute_collisions(sf::Time current_t, std::optional<Ball> cue_tip, std::vector<Ball*> balls, std::vector<TableWall*> walls);





#endif
