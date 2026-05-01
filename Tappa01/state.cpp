#include "state.h"

GameState::GameState(Gamemode mode)
{
    this->table = Table();
}

void GameState::draw(sf::RenderWindow& window)
{

    this->table.draw(window);
}
