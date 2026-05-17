#include "state.h"
#include "../utils.h"
#include <iostream>
#include "../collisions/collisions.h"
#include "gp_logic.h"

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
    // Testing
    for(unsigned i = BallIDRange::SMOOTH_START; i <= BallIDRange::SMOOTH_STOP ;++i){
        table.put_in_pocket(i);
    }
    for(unsigned i = BallIDRange::STRIPED_START; i <= BallIDRange::STRIPED_STOP ;++i){
        table.put_in_pocket(i);
    }

}

std::string Player::to_string()
{
    std::string res = "[" + this->name + "] " + std::to_string(remaining) + " Remaining | " + std::to_string(this->mistakes) + " Mistakes";
    res.append((this->smooth) ? " | Smooth" : " | Striped");
    return res;
}


void GameState::applyConfig()
{
    table.cue.type = config.cuetype;
    ss.shot_speed = 100;
    panel.setShotSpeed((int)ss.shot_speed);
    panel.setGameMode(&config);

    if(config.gamemode == SINGLE_PLAYER){
        alice = {"Alice", 14};
        bob = {"None", 0};
    } else {
        alice = {"Alice", 7, true};
        bob = {"Bob", 7, false};
    }
    current = &alice;
    other = &bob;
    panel.setCurrent(current);
    panel.setOther(other);
}


void GameState::shot(sf::Time current_t){
    if(game_ended) return;
    ss.shot_time = current_t;
    table.cue.shot(ss.shot_speed);
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
    ss.shot_speed += (delta + min_step);
    if(ss.shot_speed < 0){
        ss.shot_speed = 5;
    }else if(ss.shot_speed > 600){
        ss.shot_speed = 600;
    }
    panel.setShotSpeed(((int)ss.shot_speed));
}


void GameState::update(sf::Time current_t)
{
    if(game_ended) return;

    table.update(current_t);
    std::optional<Ball> shot_result = table.cue.advance(current_t);
    if(shot_result){
        ss.tip_copy = (*shot_result);
        ss.hitted_by = Collisions::compute_collisions(current_t, &ss.tip_copy, table.getBallsOnTable(), table.getWalls());
    } else {
        Collisions::compute_collisions(current_t, nullptr, table.getBallsOnTable(), table.getWalls());
    }

    // Valutazione dello stato della simulazione
    simulation = false;
    for(Ball* b : table.getBallsOnTable()){
        if(norm(b->getSpeed()) > 0.00005f){
            simulation = true;
        }
    }


    if(last_simulation == true && simulation == false){
        game_ended = GameLogic::round(&ss, &table, current, other, &panel, &config); // Valuta il risultato del round
        if(config.gamemode == MULTI_PLAYER){
            // Swap dei giocatori
            Player* temp = current;
            current = other;
            other = temp;
            // Aggiorno il pannello
            panel.setCurrent(current);
            panel.setOther(other);
        }
    }

    table.cue.enabled = !simulation || table.cue.isShooting();
    last_simulation = simulation;
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

