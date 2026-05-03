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
    GameState(Gamemode mode, sf::Vector2u window_size);
    void draw(sf::RenderWindow& window);
    Table table;
};

#endif
