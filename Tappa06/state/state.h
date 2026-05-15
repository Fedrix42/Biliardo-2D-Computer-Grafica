#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../structures/table/table.h"
#include <SFML/Graphics.hpp>
#include "gpstate.h"
#include "panel.h"

enum Gamemode {
    SINGLE_PLAYER,
    MULTI_PLAYER
};


class GameState {
private:
    const sf::Vector2f MIN_TABLE_MARGIN = {50, 50};
    void compute_collisions(sf::Time current_t);
    GameplayState current;
    sf::RenderWindow& window;
public:
    GameState(Gamemode mode, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    Panel panel;
    Table table;
    void resize(sf::Vector2u size);
    void shot();
    void update(sf::Time time);
    GameplayState getCurrentGameplayState();

};

#endif
