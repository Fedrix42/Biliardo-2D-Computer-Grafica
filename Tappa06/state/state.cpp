#include "state.h"
#include "../utils.h"
#include <iostream>
#include "../collisions/collisions.h"

GameState::GameState(sf::RenderWindow& window)
:   window(window),
    panel(window.getSize()),
    table({
            static_cast<float>(window.getSize().x) - MIN_TABLE_MARGIN.x,
            (static_cast<float>(window.getSize().x - MIN_TABLE_MARGIN.x) / 2.0f)
        }, {
            MIN_TABLE_MARGIN.x,
            MIN_TABLE_MARGIN.y + panel.getHeight()
        })
{
    applyConfig();
}

std::string Player::to_string()
{
    return "Round: " + this->name + " - Mistakes: " + std::to_string(this->mistakes);
}


void GameState::applyConfig()
{
    table.cue.type = config.cuetype;
    shot_speed = 100;
    panel.setMiddle(std::to_string((int)shot_speed));
    if(config.gamemode == SINGLE_PLAYER){
        alice = {"Alice", 16};
        panel.setLeft(alice.to_string());
        panel.setRight("Single player");
    } else {
        alice = {"Alice", 7};
        bob = {"Bob", 7};
        panel.setLeft(alice.to_string());
        panel.setRight("Multi player");
    }
    current = &alice;
}


void GameState::shot(){
    table.cue.shot(shot_speed);
    simulation = true;
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
        table_size.x = free_space.size.x;
        table_size.y = table_size.x / 2.0f;
        table_offset = {0,(free_space.size.y - table_size.y) / 2.0f};
        table_offset += free_space.position;
    } else { // Troppo largo
        table_size.y = free_space.size.y;
        table_size.x = table_size.y * 2.0f;
        table_offset = {(free_space.size.x - table_size.x) / 2.0f, 0};
        table_offset += free_space.position;
    }

    table.resize(table_size, table_offset);

}

void GameState::set_shot_speed_delta(float delta)
{
    float min_step = (delta > 0) ? 5 : -5;
    shot_speed += (delta + min_step);
    if(shot_speed < 0){
        shot_speed = 5;
    }else if(shot_speed > 600){
        shot_speed = 600;
    }
    panel.setMiddle(std::to_string((int)shot_speed));
}


void GameState::update(sf::Time current_t)
{
    table.update(current_t);
    std::vector<Ball*> hitted_by_cue = compute_collisions(current_t, table.cue.advance(current_t), table.getBallsOnTable(), table.getWalls());
    // Controllo se il round è terminato (Tutte le palline sul tavolo sono ferme)
    simulation = false;
    for(Ball* b : table.getBallsOnTable()){
        if(norm(b->getSpeed()) > 0.00001f){
            simulation = true;
        }
    }
    if(!simulation){
        computeRoundResult(hitted_by_cue);
    }
}

void GameState::computeRoundResult(std::vector<Ball*> hitted_by_cue)
{
    size_t hitted_size = hitted_by_cue.size();

    if(hitted_size == 0) return;
    if(hitted_size == 1 && hitted_by_cue.at(0)->getID() == BallIDRange::WHITE){

    } else {
        current->mistakes++;
        panel.setLeft(current->to_string());
        if(current->mistakes >= config.MAX_PLAYER_MISTAKES){
            panel.setMiddle("Alice, you lost!", true);
        }
    }
}



void GameState::draw(sf::RenderWindow& window)
{
    panel.draw(window);
    table.draw(window);
}

bool GameState::isSimulationRunning()
{
    return simulation;
}

