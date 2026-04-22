#include <SFML/Graphics.hpp>



//////////////////////
// Initial defaults //
//////////////////////

// window
const char* window_title = "blockbreaker";
const unsigned window_width = 800;
const unsigned window_height = 600;
const float max_frame_rate = 60;

const float ball_radius = 10.0;
const sf::Vector2f paddle_size = {100.0, 16.0};

struct Ball {
    float radius;
    int speed; // Pixels per seconds
    sf::Vector2f pos;
    sf::Texture texture;

    Ball(){
        speed = 3;
        texture = sf::Texture("./texture_ball.png");
        radius = ball_radius;
        pos = {window_width / 2, window_height - radius - paddle_size.y};
    }
    
    void draw(sf::RenderWindow& window){
        auto circle = sf::CircleShape(radius);
        circle.setTexture(&texture);
        circle.setOrigin({radius, radius});
        circle.setPosition(pos);
        window.draw(circle);
    }

    void move(sf::RenderWindow& window){
        if(pos.y < radius || pos.y > window.getSize().y - radius - paddle_size.y){
            speed = -speed;
        }
        pos = {pos.x, pos.y - speed};
    }
};

struct Paddle {
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Texture texture;
    
    Paddle(){
        texture = sf::Texture("./texture_paddle.png");
        size = paddle_size;
        pos = {window_width / 2, window_height};
    }
    void draw(sf::RenderWindow& window){
        auto rect = sf::RectangleShape(size);
        rect.setTexture(&texture);
        rect.setOrigin({size.x / 2, size.y});
        rect.setPosition(pos);
        window.draw(rect);
    }
};


struct State {
    Paddle paddle;
    Ball ball;

    State(){}
    void draw(sf::RenderWindow& window){
        ball.draw(window);
        paddle.draw(window);
    }

};

State state;

////////////
// Events //
////////////

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
    switch(pressed.code){
        case (sf::Keyboard::Key::Left):
            if(state.paddle.pos.x > 0 + paddle_size.x / 2){
                state.paddle.pos.x -= 5; 
            }
            break;

        case (sf::Keyboard::Key::Right):
            if(state.paddle.pos.x < window_size.x - + paddle_size.x / 2){
                state.paddle.pos.x += 5;
            }
            break;
        default:
            break;
    }
}

//////////
// Loop //
//////////


int main()
{
    sf::RenderWindow window (sf::VideoMode ({window_width, window_height}), window_title);
    window.setFramerateLimit (max_frame_rate);
    window.setMinimumSize(window.getSize());
    sf::Clock clock;
    clock.start();
    sf::Time last = clock.getElapsedTime();
    while (window.isOpen())
    {
        // events
        window.handleEvents (
            [&window](const sf::Event::Closed&) { handle_close (window); },
            [&window](const sf::Event::Resized& event) { handle_resize (event, window); },
            [&window](const sf::Event::KeyPressed& event) { handle_movement (event, window); }
        );
        
        // display
        window.clear (sf::Color::Black);
        
        if(clock.getElapsedTime().asMilliseconds() - last.asMilliseconds() > 16){ // 60 fps
            state.ball.move(window);
            last = clock.getElapsedTime();
        }
        state.draw(window);

        window.display ();
    }
}
