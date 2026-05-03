#include "events.h"

// Window events
void handle_close(sf::RenderWindow& window, GameState& state)
{
    window.close();
}
void handle_resize(const sf::Event::Resized& resized, sf::RenderWindow& window)
{
}

// Keyboard events
void handle_key_pressed(const sf::Event::KeyPressed* pressed, sf::RenderWindow& window, GameState& state)
{
}
void handle_key_released(const sf::Event::KeyReleased* released, sf::RenderWindow& window, GameState& state)
{
}

void handle_text_entered(const sf::Event::TextEntered* text_entered, sf::RenderWindow& window, GameState& state)
{
}

// Mouse Events
void handle_mouse_pressed(const sf::Event::MouseButtonPressed* pressed, sf::RenderWindow& window, GameState& state)
{
}
void handle_mouse_released(const sf::Event::MouseButtonReleased* released, sf::RenderWindow& window, GameState& state)
{
}
void handle_mouse_moved(const sf::Event::MouseMoved* moved, sf::RenderWindow& window, GameState& state)
{
    state.table.cue.update_position(moved);
}
void handle_mouse_wheel_scrolled(const sf::Event::MouseWheelScrolled* wheel_scrolled, sf::RenderWindow& window, GameState& state)
{
}

void handle_mouse_left(const sf::Event::MouseLeft* event, sf::RenderWindow&window, GameState& state){
    state.table.cue.setHide(false);
}

void handle_mouse_entered(const sf::Event::MouseEntered* event, sf::RenderWindow&window, GameState& state){
    state.table.cue.setHide(true);
}
