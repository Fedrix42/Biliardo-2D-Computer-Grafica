#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

/*
L'interfaccia "collisore" permette di verificare se sta avvenendo una collisione
tra due oggetti e identificare il punto di impatto ed altre informazioni
*/
class Collider;

struct Collision {
    sf::Vector2f normal; // Perpendiolare e normalizzato al punto di impatto
    sf::Vector2f collision_point; // Punto di collisione
    bool applied = false;
};

class Collider {
public:
    virtual ~Collider() = default;
    // Core
    std::unordered_map<Collider*, Collision> collisions; //  Collisioni tra me e gli altri
    std::vector<Collision> computeCollisions(Collider* collider); // Calcola il punto di impatto con "alta" precisione (costoso)
    bool doesBoundBoxesCollide(Collider* collider); // Calcola la possibile collisione in maniera economica tramite la bound box
    // Physics
    float velocityAlongNormal(Collider* collider) const; // Velocità lungo la direzione normale
    // Setter e getter
    virtual std::string to_string() const = 0;
    virtual sf::Vector2f getSpeed() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual float getMass() const = 0;
    virtual void setSpeed(sf::Vector2f speed) = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
private:
    virtual sf::FloatRect getBoundBox() const = 0;
    virtual std::vector<sf::Vector2f> getHitbox() const = 0;
};



#endif
