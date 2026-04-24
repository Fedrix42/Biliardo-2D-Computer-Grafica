#ifndef EVENTS_H
#define EVENTS_H
#include <SFML/Graphics.hpp>
#include "state.h"

void handle_close(sf::RenderWindow& window, State& state);
void handle_resize (const sf::Event::Resized& resized, sf::RenderWindow& window);

void handle_key_pressed(const sf::Event::KeyPressed* pressed, sf::RenderWindow& window, State& state);
void handle_key_released(const sf::Event::KeyReleased* released, sf::RenderWindow& window, State& state);

void handle_text_entered(const sf::Event::TextEntered* text_entered, sf::RenderWindow& window, State& state);


void handle_mouse_pressed(const sf::Event::MouseButtonPressed* pressed, sf::RenderWindow& window, State& state);
void handle_mouse_released(const sf::Event::MouseButtonReleased* released, sf::RenderWindow& window, State& state);
void handle_mouse_moved(const sf::Event::MouseMoved* moved, sf::RenderWindow& window, State& state);
void handle_mouse_wheel_scrolled(const sf::Event::MouseWheelScrolled* wheel_scrolled, sf::RenderWindow& window, State& state);



#endif