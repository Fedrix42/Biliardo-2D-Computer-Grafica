#include "state.h"
#include "../utils.h"
#include <iostream>

GameState::GameState(Gamemode mode, sf::RenderWindow& window)
    : current(GameplayState::PLAYER_ACTION),
    window(window),
    panel(window.getSize()),
    table({
            static_cast<float>(window.getSize().x) - MIN_TABLE_MARGIN.x,
            (static_cast<float>(window.getSize().x - MIN_TABLE_MARGIN.x) / 2.0f)
        }, {
            MIN_TABLE_MARGIN.x,
            MIN_TABLE_MARGIN.y + panel.getHeight()
        })
{}

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
    auto balls = table.getBalls();
    auto walls = table.getWalls();
    for(Ball* b : balls){
        for(TableWall* w : walls){
            //std::cout << std::boolalpha << doesBoundBoxesCollide(b, w) << std::endl;
            if(doesBoundBoxesCollide(b, w) && b->walls_collisions.find(w) == b->walls_collisions.end()){
                std::cout << b->to_string() << std::endl;
                auto res = computeCollision(b, w, current_t);
                if(res){
                    b->walls_collisions[w] = (*res);
                }
            }
        }
    }
    for(size_t i = 0; i < balls.size(); ++i){
        for(size_t j = i + 1; j < balls.size(); ++j){
            Ball* self = balls.at(i);
            Ball* collider = balls.at(j);
            auto self_collisions = self->balls_collisions;
            auto collider_collisions = collider->balls_collisions;
            if(doesBoundBoxesCollide(self, collider)
                && self_collisions.find(collider) == self_collisions.end()
                && collider_collisions.find(self) == collider_collisions.end()){
                    //std::cout << self->to_string() << " con " << collider->to_string() << std::endl;
                    auto res = computeCollision(self, collider, current_t);
                    if(res){
                        self->balls_collisions[collider] = (*res).first;
                        collider->balls_collisions[self] = (*res).second;
                    }
            }
        }
    }

}

void GameState::resize(sf::Vector2u size){

    // Voglio mantenere un rapporto di 2:1 col tavolo
    panel.resize(size);
    sf::FloatRect free_space = sf::FloatRect(
        {MIN_TABLE_MARGIN.x, panel.getHeight() + MIN_TABLE_MARGIN.y},
        {size.x - (2.0f * MIN_TABLE_MARGIN.x), size.y - panel.getHeight() - (2.0f * MIN_TABLE_MARGIN.y)}
    );

    float target_rateo = 2.0f / 1.0f;
    float current_rateo = static_cast<float>(size.x - (2.0f * MIN_TABLE_MARGIN.x)) / static_cast<float>(size.y - panel.getHeight() - (2 * MIN_TABLE_MARGIN.y));
    sf::Vector2f table_offset;
    sf::Vector2f table_size;

    if(target_rateo > current_rateo){ // Troppo alto
        //std::cout  << "Troppo alto" << std::endl;
        table_size.x = free_space.size.x;
        table_size.y = table_size.x / 2.0f;
        table_offset = {0,(free_space.size.y - table_size.y) / 2.0f};
        table_offset += free_space.position;
        //std::cout << point_to_str(table_size) << " - " << point_to_str(table_offset) << std::endl;
    } else { // Troppo largo
        //std::cout  << "Troppo largo" << std::endl;
        table_size.y = free_space.size.y;
        table_size.x = table_size.y * 2.0f;
        table_offset = {(free_space.size.x - table_size.x) / 2.0f, 0};
        table_offset += free_space.position;
        //std::cout << point_to_str(table_size)<< " - " << point_to_str(table_offset) << std::endl;
    }

    table.resize(table_size, table_offset);

}

void GameState::update(sf::Time current_t)
{
    table.update(current_t);
    compute_collisions(current_t);
}


void GameState::draw(sf::RenderWindow& window)
{
    panel.draw(window);
    table.draw(window, current);
}
