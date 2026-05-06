#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <vector>
/*
L'interfaccia "collisore" permette di verificare se sta avvenendo una collisione
tra due oggetti e identificare il punto di impatto ed altre informazioni
*/
class Collider;

struct Collision {
    sf::Vector2f collision_point; // Punto di collisione
    sf::Vector2f position_at_collision; // Posizione al momento della collisione
    sf::Vector2f collider_speed; // Oggetto con in quale si collide
    float collider_mass;
};

class Collider {
public:
    virtual ~Collider() = default;
    void computeAndSetCollision(Collider* collider); // Calcola il punto di impatto con "alta" precisione (costoso)
    bool doesBoundBoxesCollide(Collider* collider); // Calcola la possibile collisione in maniera economica tramite la bound box
    std::vector<Collision> getFutureCollisions();
    virtual std::string to_string() const = 0;
    virtual sf::Vector2f getSpeed() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual float getMass() const = 0;
    virtual void setSpeed(sf::Vector2f speed) = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
private:
    std::vector<Collision> futureCollisions; // Posso avere più collisioni
    virtual sf::FloatRect getBoundBox() const = 0;
    virtual std::vector<sf::Vector2f> getHitbox() const = 0;
};



#endif
