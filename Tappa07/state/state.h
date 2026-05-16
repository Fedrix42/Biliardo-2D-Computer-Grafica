#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "../structures/table/table.h"
#include "panel.h"
#include "config.h"

struct Player {
    std::string name;
    unsigned int remaining;
    unsigned int mistakes = 0; // Numero di falli effettuati
    std::string to_string();
};

struct ShotState {
    sf::Time shot_time;
    float shot_speed = 100;
    std::vector<Ball*> hitted_by;
};


class GameState {
private:
    const sf::Vector2f MIN_TABLE_MARGIN = {50, 50};
    bool simulation = false;
    sf::RenderWindow& window;
    Player bob;
    Player alice;
    Player* current;
    bool game_ended = false;
    void applyConfig();
    void computeRoundResult();
    void increase_mistakes();
public:
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
