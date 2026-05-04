#ifndef CUE_H
#define CUE_H
#include "ball.h"
#include <SFML/Graphics.hpp>

/*
La stecca ruota attorno ad un punto di ancoraggio che è una delle biglie che
stanno sul tavolo. La biglia di ancoraggio viene selezionata dal giocatore con
il cursore del mouse. Ruotando il giocatore può impostare l'angolo di tiro.
*/
class Cue {
public:
    Cue();
    void update_position(const sf::Event::MouseMoved* moved);
    void draw(sf::RenderWindow& window);
    void setAnchor(Ball* anchor);
    Ball* getAnchor();
    void setHide(bool h);
    float getMass();
    float getSpeed();
    sf::Vector2f getDirection();
private:
    bool hide;
    sf::ConvexShape shape;
    sf::Vector2f impact; // Punto di impatto
    sf::Vector2f direction; // Direzione normalizzata del colpo
    Ball* anchor;
    double weight = 0.5; // 0.5 kg
    float speed; // Forza del colpo definito come vettore di velocità (metri al secondo)
};

#endif
