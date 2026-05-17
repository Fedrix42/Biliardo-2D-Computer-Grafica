#ifndef CUE_H
#define CUE_H
#include "ball.h"
#include <SFML/Graphics.hpp>

enum CueType {
    ANCHOR,
    FREE
};



class Cue {
public:
    Cue(sf::Vector2f position);
    void update(const sf::Event::MouseMoved* moved);
    void draw(sf::RenderWindow& window);
    void shot(float speed);
    std::optional<Ball> advance(sf::Time current_t); // Restituisce una pallina virtuale da far collidere con le altre
    bool isShooting();
    void rotate(bool clockwise);
    Ball* anchor;
    CueType type = CueType::ANCHOR;
    bool enabled = true; // Disabilita o abilita l'aggiornamento della stecca e la visualizzazione
private:
    const float CUE_WIDTH = 8.0f;
    const float BODY_HEIGHT = 500.0f;
    const float animation_backward_speed = 30.0f; // Indietro di -5 px al secondo
    const sf::Vector2f local_tip = {CUE_WIDTH / 2.0f, 0.0f};
    const float ROTATION_ANGLE_DEGREE = 2;
    float mass = 0.5; // 0.5 kg
    sf::RectangleShape body;
    sf::CircleShape tip;
    bool shooting = false;
    sf::Vector2f direction; // Direzione del colpo normalizzata
    float speed;
    bool backward = true;
    sf::Time last = sf::Time::Zero;
    sf::Time shot_start_animation = sf::Time::Zero;
};

#endif
