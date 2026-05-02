#include "state.h"

GameState::GameState(Gamemode mode, sf::Vector2u window_size)
    : table(window_size, { 0, 0 })
{
}

void GameState::draw(sf::RenderWindow& window)
{

    this->table.draw(window);
}
