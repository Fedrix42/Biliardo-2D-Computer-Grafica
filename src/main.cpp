#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.h"
#include "paddle.h"
#include "ball.h"
#include "state.h"

//////////
// Loop //
//////////


int main(){
    State* state = new State(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    sf::RenderWindow window (sf::VideoMode ({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), WINDOW_TITLE);
    window.setMinimumSize(window.getSize());
    sf::Clock clock;
    clock.start();
    sf::Time last = clock.getElapsedTime();
    while (window.isOpen())
    {
        // events
        /*
        window.handleEvents (
            [&window](const sf::Event::Closed&) { handle_close (window); },
            [&window](const sf::Event::Resized& event) { handle_resize (event, window); },
            [&window](const sf::Event::KeyPressed& event) { handle_movement (event, window); }
        );*/
        
        // display
        window.clear (sf::Color::Black);
        
        if(clock.getElapsedTime().asMilliseconds() - last.asMilliseconds() > 16){ // 60 fps
            state->ball->move(window);
            last = clock.getElapsedTime();
        }
        state->draw(window);

        window.display ();
    }
}
