#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "strutture/table.h"
#include <SFML/Graphics.hpp>

enum Gamemode {
    SINGLE_PLAYER,
    MULTI_PLAYER
};

class GameState {
public:
    GameState(Gamemode mode);
    void draw(sf::RenderWindow& window);

private:
    Table table;
};

#endif