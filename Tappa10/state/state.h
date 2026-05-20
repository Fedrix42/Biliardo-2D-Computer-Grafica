#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "../structures/table/table.h"
#include "panel.h"
#include "config.h"
#include "shotstate.h"
#include "player.h"

/*
Stato globale del gioco, gestione delle azioni del giocatore e mantenimento delle strutture necessarie.
*/


class GameState {
private:
    const sf::Vector2f MIN_TABLE_MARGIN = {50, 50};
    bool simulation = false;
    bool last_simulation = false;
    sf::RenderWindow& window;
    Player bob;
    Player alice;
    Player* current;
    Player* other;
    bool game_ended = false;
public:
    void apply_config();
    GameState(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    Panel panel;
    Table table;
    void resize(sf::Vector2u size);
    GameConfig config;
    void shot(sf::Time current_t);
    void set_shot_speed_delta(float delta);
    void update(sf::Time time);
    bool isSimulationRunning();
    ShotState ss;
};

#endif
