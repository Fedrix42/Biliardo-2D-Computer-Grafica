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
    ss.shot_speed = 100;
    panel.setMiddle(std::to_string((int)ss.shot_speed));

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


void GameState::shot(sf::Time current_t){
    ss.shot_time = current_t;
    table.cue.shot(ss.shot_speed);
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
    ss.shot_speed += (delta + min_step);
    if(ss.shot_speed < 0){
        ss.shot_speed = 5;
    }else if(ss.shot_speed > 600){
        ss.shot_speed = 600;
    }
    panel.setMiddle(std::to_string((int)ss.shot_speed));
}


void GameState::update(sf::Time current_t)
{
    table.update(current_t);
    std::optional<Ball> shot_result = table.cue.advance(current_t);
    std::vector<Ball*> hitted_by_cue = compute_collisions(current_t, shot_result, table.getBallsOnTable(), table.getWalls());
    if(shot_result){
        ss.hitted_by = hitted_by_cue;
    }

    // Controllo se il round è terminato (Tutte le palline sul tavolo sono ferme)
    // Lo faccio solo ogni 500 ms perchè la compute collisions genera collisioni nel futuro
    // quindi devo dare alle palline il tempo di catturare quelle collisioni future
    if((current_t - ss.shot_time).asSeconds() > 1 && simulation){
        simulation = false;
        for(Ball* b : table.getBallsOnTable()){
            if(norm(b->getSpeed()) > 0.00005f){
                simulation = true;
            }
        }
    }
    if(!simulation){
        computeRoundResult();
    }

}

void GameState::increase_mistakes(){
    current->mistakes++;
    panel.setLeft(current->to_string());
    if(current->mistakes >= config.MAX_PLAYER_MISTAKES){
        panel.setMiddle("Alice, you lost! To many mistakes...");
        game_ended = true;
        return;
    }
}

void GameState::computeRoundResult()
{
    size_t hitted_size = ss.hitted_by.size();
    fflush(stdout);
    if(hitted_size == 0) return;
    std::vector<Ball*> now_putted_in_pockets;

    // Conto le palline messe in buca dal giocatore corrente
    for(unsigned int i = BallIDRange::TOTAL_START; i <= BallIDRange::TOTAL_STOP; ++i){
        auto& entry = table.balls.at(i);
        if(entry.pocket != nullptr && !entry.counted){
            now_putted_in_pockets.push_back(&entry.ball);
            entry.counted = true;
        }
    }
    // Controllo che non ha colpito più una 1 pallina oppure non la bianca, altrimenti è un fallo
    if(hitted_size > 1 || ss.hitted_by.at(0)->getID() != BallIDRange::WHITE){
        increase_mistakes();
    }

    // Verifica della messa in buca della nera o della bianca
    for(Ball* putted : now_putted_in_pockets){
        if(((config.gamemode == SINGLE_PLAYER && current->remaining > 1) || (config.gamemode == MULTI_PLAYER && current->remaining > 1))
            && putted->getID() == BallIDRange::BLACK){
            panel.setMiddle(current->name + ", you lost! You put the ball 8 in the pocket...");
            game_ended = true;
            return;
        }
        if(putted->getID() == BallIDRange::WHITE){
            increase_mistakes();
            table.reset_white();
        }
    }

    switch(config.gamemode){
        case SINGLE_PLAYER:
            break;
        case MULTI_PLAYER:
            break;
    }

    ss.hitted_by = std::vector<Ball*>();
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

