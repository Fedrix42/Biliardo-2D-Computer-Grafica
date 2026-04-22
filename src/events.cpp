/*
#include <SFML/Graphics.hpp>

void handle_close (sf::RenderWindow& window)
{
    window.close();
}
void handle_resize (const sf::Event::Resized& resized, sf::RenderWindow& window)
{   // constrain aspect ratio and map always the same portion of the world
    float aspect = static_cast<float>(window_width)/static_cast<float>(window_height);
    sf::Vector2u ws = resized.size;
    float new_aspect = static_cast<float>(ws.x)/static_cast<float>(ws.y);
    if (new_aspect < aspect)
        ws = {ws.x,static_cast<unsigned>(ws.x/aspect)};
        else
        ws = {static_cast<unsigned>(ws.y*aspect),ws.y};
    window.setSize(ws);
}

void handle_movement(const sf::Event::KeyPressed& pressed, sf::RenderWindow& window){
    auto window_size = window.getSize();
    int pixel_movement = compute_relative_speed(PADDLE_SPEED, window_size.y);
    switch(pressed.code){
        case (sf::Keyboard::Key::Left):
            if(state.paddle.pos.x > 0 + paddle_size.x / 2){
                state.paddle.pos.x -= pixel_movement; 
            }
            break;

        case (sf::Keyboard::Key::Right):
            if(state.paddle.pos.x < window_size.x + paddle_size.x / 2){
                state.paddle.pos.x += pixel_movement;
            }
            break;
        default:
            break;
    }
}*/