#include <SFML/Graphics.hpp>
#include <atomic>
#include <csignal>
#include <iostream>
#include "main.h"
#include "state/state.h"
#include "assetmgr.h"
#include "state/menu.h"

std::atomic<bool> termination_signal_receive(false);

void signal_handler(int)
{
    termination_signal_receive = true;
}

void handle_close(sf::RenderWindow& window, GameState& state)
{
    window.close();
}
void handle_resize(const sf::Event::Resized* resized, sf::RenderWindow& window, GameState& state, sf::Sprite* background, Menu& menu)
{
    window.setView(sf::View(sf::FloatRect({0, 0}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)})));
    // Dimensione texture
    sf::Vector2u textureSize = background->getTexture().getSize();
    background->setScale({
        static_cast<float>(resized->size.x) / textureSize.x,
        static_cast<float>(resized->size.y) / textureSize.y
    });
    state.resize(resized->size);
    menu.resize(resized->size);
}

// Keyboard events
void handle_key_pressed(const sf::Event::KeyPressed* pressed, sf::RenderWindow& window, GameState& state, sf::Time current_t)
{
    if(pressed->code == sf::Keyboard::Key::K){
        state.shot(current_t);
    } else if(pressed->code == sf::Keyboard::Key::D){
        state.table.cue.rotate(true);
    } else if(pressed->code == sf::Keyboard::Key::A){
        state.table.cue.rotate(false);
    }
}


// Mouse Events
void handle_mouse_pressed(const sf::Event::MouseButtonPressed* pressed, sf::RenderWindow& window, GameState& state, Menu& menu)
{
    if(menu.active){
        menu.click_event(&state.config, pressed->position);
        state.apply_config();
    }
}

void handle_mouse_moved(const sf::Event::MouseMoved* moved, sf::RenderWindow& window, GameState& state, Menu& menu)
{
    if(menu.active){
        menu.hover(moved->position);
    }else if(!state.isSimulationRunning()){
        state.table.cue.update(moved);
    }

}
void handle_mouse_wheel_scrolled(const sf::Event::MouseWheelScrolled* wheel_scrolled, sf::RenderWindow& window, GameState& state)
{
    state.set_shot_speed_delta(wheel_scrolled->delta);
}


int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    sf::RenderWindow window(sf::VideoMode({ DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT }), WINDOW_TITLE);
    GameState state = GameState(window);
    Menu menu = Menu(window.getSize());
    window.setMinimumSize(window.getSize());
    window.setFramerateLimit(240);

    sf::Sprite background(*AssetMGR::instance().background_texture());


    sf::Clock clock;
    clock.start();
    while (window.isOpen() && !termination_signal_receive) {
        while (const std::optional event_opt = window.pollEvent()) {
            if (event_opt->is<sf::Event::Closed>()) {
                handle_close(window, state);
            } else if (const auto* event = event_opt->getIf<sf::Event::Resized>()) {
                handle_resize(event, window, state, &background, menu);
            } else if (const auto* event = event_opt->getIf<sf::Event::KeyPressed>()) {
                handle_key_pressed(event, window, state, clock.getElapsedTime());
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseButtonPressed>()) {
                handle_mouse_pressed(event, window, state, menu);
            }  else if (const auto* event = event_opt->getIf<sf::Event::MouseMoved>()) {
                handle_mouse_moved(event, window, state, menu);
            } else if (const auto* event = event_opt->getIf<sf::Event::MouseWheelScrolled>()) {
                handle_mouse_wheel_scrolled(event, window, state);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(background);
        if(menu.active){
            menu.draw(window);
        } else {
            state.update(clock.getElapsedTime());
            state.draw(window);
        }
        window.display();
    }
}
