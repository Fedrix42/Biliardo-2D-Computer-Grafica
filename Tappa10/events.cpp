#include "events.h"


// Window events
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
void handle_key_released(const sf::Event::KeyReleased* released, sf::RenderWindow& window, GameState& state)
{
}

void handle_text_entered(const sf::Event::TextEntered* text_entered, sf::RenderWindow& window, GameState& state)
{
}

// Mouse Events
void handle_mouse_pressed(const sf::Event::MouseButtonPressed* pressed, sf::RenderWindow& window, GameState& state, Menu& menu)
{
    if(menu.active){
        menu.click_event(&state.config, pressed->position);
        state.apply_config();
    }
}

void handle_mouse_released(const sf::Event::MouseButtonReleased* released, sf::RenderWindow& window, GameState& state)
{
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

void handle_mouse_left(const sf::Event::MouseLeft* event, sf::RenderWindow&window, GameState& state){
}

void handle_mouse_entered(const sf::Event::MouseEntered* event, sf::RenderWindow&window, GameState& state){
}
