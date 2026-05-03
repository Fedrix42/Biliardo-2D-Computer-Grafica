#include "main.h"
#include "events.h"
#include "state.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <csignal>
#include <iostream>

std::atomic<bool> termination_signal_receive(false);

void signal_handler(int)
{
    termination_signal_receive = true;
}

int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    sf::RenderWindow window(sf::VideoMode({ DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT }), WINDOW_TITLE);
    GameState state = GameState(Gamemode::SINGLE_PLAYER, window);
    window.setMinimumSize(window.getSize());
    window.setFramerateLimit(140);
    sf::Clock clock;
    while (window.isOpen() && !termination_signal_receive) {
        while (const std::optional event_opt = window.pollEvent()) {
            if (event_opt->is<sf::Event::Closed>()) {
                handle_close(window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::KeyPressed>()) {
                handle_key_pressed(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::KeyReleased>()) {
                handle_key_released(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseButtonPressed>()) {
                handle_mouse_pressed(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseButtonReleased>()) {
                handle_mouse_released(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseMoved>()) {
                handle_mouse_moved(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseWheelScrolled>()) {
                handle_mouse_wheel_scrolled(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::TextEntered>()) {
                handle_text_entered(event, window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseLeft>()){
                handle_mouse_left(event, window, state);
            } else if(const auto* event = event_opt->getIf<sf::Event::MouseEntered>()){
                handle_mouse_entered(event, window, state);
            }
        }

        state.update(clock.restart());
        window.clear(sf::Color::Black);
        state.draw(window);
        window.display();
    }
}
