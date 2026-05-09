#include "state.h"
#include "../utils.h"
#include <iostream>

GameState::GameState(Gamemode mode, sf::RenderWindow& window)
    : table(window.getSize(), { 0, 0 }), current(GameplayState::PLAYER_ACTION), window(window)
{
}

/*
Colpo tra la stecca e una pallina.
Implementato con un urto monodimensionale:

Data:
    - La massa della stecca
    - La velocità iniziale (al momento dell'impatto) della stecca
    - La massa della pallina
    - La velocità della palline (0 px / s)

Calcolo la velocità finale di stecca e pallina.
La velocità finale della pallina, che è quella che ci interessa, è un numero in pixel al secondo.
A questa norma gli applico la direzione del tiro, presa dalla stecca, così da avere una velocità
definita bidimensionale in quanto questa è quella che si usa per i calcoli negli urti bidimensionali
che userò per i rimbalzi.
*/

void GameState::shot(){
    if(current == GameplayState::SIMULATION)
        return; // Non si puo colpire nuovamente durante la simulazione. Bisogna aspettare termini.
    current = GameplayState::SIMULATION;
    Cue cue = table.cue;
    Ball* ball = cue.getAnchor();

    // float cue_final_speed = fnspeedA_1D(cue.getMass(), ball->getMass(), cue.getSpeed(), 0); Utile per l'animazione di rimbalzo
    // cue_final_speed = meter_to_pixel(cue_final_speed);
    float ball_final_speed = fnspeedA_1D(ball->getMass(), cue.getMass(), 0, cue.getSpeed());
    sf::Vector2f vectorized_ball_speed = cue.getDirection() * ball_final_speed;
    std::cout << "Colpendo a " << cue.getSpeed() << " px/s la velocità finale della pallina è "
        << ball_final_speed << " px/s ("
        << vectorized_ball_speed.x << "," << vectorized_ball_speed.y << ")" << std::endl;

    ball->setSpeed(vectorized_ball_speed);
}

void  GameState::compute_collisions(sf::Time current_t){
    auto colliders = table.getColliders();
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            Collider* c1 = colliders[i];
            Collider* c2 = colliders[j];
            if (c1->doesBoundBoxesCollide(c2) && c1->collisions.find(c2) == c1->collisions.end() && c2->collisions.find(c1) == c2->collisions.end()) {
                auto result = c1->computeCollisions(c2, current_t);
                if(result){
                    //std::cout << "Collisione tra " << c1->to_string() << " e " << c2->to_string() << std::endl;
                    c1->collisions[c2] = (*result).first;
                    c2->collisions[c1] = (*result).second;
                }
            }
        }
    }
}

void GameState::update(sf::Time current_t)
{
    table.update(current_t);
    compute_collisions(current_t);
}


void GameState::draw(sf::RenderWindow& window)
{
    this->table.draw(window, current);
}
