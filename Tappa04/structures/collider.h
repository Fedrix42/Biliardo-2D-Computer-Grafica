#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <vector>
/*
L'interfaccia "collisore" permette di verificare se sta avvenendo una collisione
tra due oggetti e identificare il punto di impatto ed altre informazioni
*/

class Collider {
public:
    virtual ~Collider() = default;
    std::optional<sf::Vector2f> collision_point(Collider* collider); // Calcola il punto di impatto con "alta" precisione (costoso)
    bool doesBoundBoxesCollide(Collider* collider); // Calcola la possibile collisione in maniera economica tramite la bound box
    virtual sf::FloatRect getBoundBox() const = 0;
    virtual std::vector<sf::Vector2f> getHitbox() const = 0;
    virtual std::string to_string() const = 0;
    virtual sf::Vector2f getSpeed() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setSpeed(sf::Vector2f speed) = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
};

#endif
