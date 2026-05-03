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
    GameState(Gamemode mode, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    Table table;
    void shot();
    void update(sf::Time time);
private:
    sf::RenderWindow& window;
};

#endif
