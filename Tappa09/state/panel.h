#ifndef PANEL_H
#define PANEL_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include "config.h"

class Panel {
public:
    Panel(sf::Vector2u window_size);
    void resize(sf::Vector2u size);
    void draw(sf::RenderWindow& window);
    float getHeight();
    void setShotSpeed(int speed);
    void setGameMode(GameConfig* config);
    void setCurrent(Player* current);
    void setOther(Player* other);
    void setMessage(std::string msg);
    bool clickedOnMenuButton(sf::Vector2i cursor);
private:
    const float PANEL_HEIGHT = 50;
    sf::Vector2u window_size;
    sf::Font font;
    sf::RectangleShape background;
    // Sezione alta
    sf::Text menu_button_label;
    sf::Text shot_speed_label;
    sf::Text game_config_label;
    // Sezione bassa
    sf::Text curr_player_label;
    sf::Text curr_player_indicator_label;
    sf::Text other_player_label;
    const float xmargin = 5;
};


#endif

