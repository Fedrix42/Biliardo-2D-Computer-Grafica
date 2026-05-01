#ifndef CUE_H
#define CUE_H
#include "ball.h"
#include <SFML/Graphics.hpp>

/*
La stecca ruota attorno ad un punto di ancoraggio che è una delle biglie che
stanno sul tavolo. La biglia di ancoraggio viene selezionata dal giocatore con
il cursore del mouse. Ruotando il giocatore può impostare l'angolo di tiro.
*/

class CueView {
public:
    CueView();
    ~CueView() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    sf::RectangleShape shape;
    sf::Texture texture;
};

class Cue {
public:
    Cue();
    ~Cue() = default;
    void draw(sf::RenderWindow& window);

private:
    Ball anchor;
    double weight = 0.5; // 0.5 kg
};

#endif