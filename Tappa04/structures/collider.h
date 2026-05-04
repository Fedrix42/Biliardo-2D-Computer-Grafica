#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

/*
L'interfaccia "collisore" permette di verificare se sta avvenendo una collisione
tra due oggetti e identificare il punto di impatto ed altre informazioni
*/
class Collider {
public:
    virtual ~Collider() = default;
    virtual sf::FloatRect getBounds() const = 0; // Metodo non implementato che non cambia la classe
    virtual void onCollision(Collider& other) = 0; // Cosa fare in caso di collisione
    virtual sf::Vector2f getSpeed() const = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual sf::Vector2f setSpeed() = 0;
    virtual sf::Vector2f setPosition() = 0;
};

#endif
