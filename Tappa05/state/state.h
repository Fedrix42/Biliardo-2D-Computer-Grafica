#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../structures/table/table.h"
#include <SFML/Graphics.hpp>
#include "gpstate.h"

enum Gamemode {
    SINGLE_PLAYER,
    MULTI_PLAYER
};


class GameState {
public:
    GameState(Gamemode mode, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    Table table;
    void shot();
    void update(sf::Time time);
    GameplayState getCurrentGameplayState();
private:
    void compute_collisions(sf::Time current_t);
    GameplayState current;
    sf::RenderWindow& window;
};

#endif
