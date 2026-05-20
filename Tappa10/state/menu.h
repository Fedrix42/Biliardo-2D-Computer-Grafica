#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "config.h"

struct Label {
    Label(sf::Font& font, std::string str, bool clickable);
    void draw(sf::RenderWindow& window);
    sf::Text text;
    sf::RectangleShape border;
    bool state = false; // On oppure off, cambia quando si clicca
    void set_size(sf::Vector2f size);
    void set_position(sf::Vector2f position);
    sf::FloatRect get_bounds();
    bool clicked(sf::Vector2i cursorpos);
    bool hover(sf::Vector2i cursorpos);
    bool clickable;
};

struct OptionsBlock {
    OptionsBlock(sf::Font& font, std::string t, std::string l, std::string r);
    void draw(sf::RenderWindow& window);
    Label title;
    Label left;
    Label right;
    std::optional<bool> clicked(sf::Vector2i cursorpos); //  left / right, stato della label, left == true
    bool hover(sf::Vector2i cursorpos);
    void set_position(sf::Vector2f position);
    sf::FloatRect get_bounds();
    const sf::Vector2f margin = {5.0f, 5.0f};
    const sf::Vector2f title_size = {500, 40};
};

class Menu {
public:
    Menu(sf::Vector2u window_size);
    void resize(sf::Vector2u size);
    void draw(sf::RenderWindow& window);
    bool active = true;
    void click_event(GameConfig* config, sf::Vector2i cursorpos);
    void hover(sf::Vector2i cursorpos);
private:
    sf::Font font;
    OptionsBlock cue_opts;
    OptionsBlock diff_opts;
    Label single_player_option;
    Label multi_player_option;
    Label play_button;
    const float YMARGIN = 20.0f;
    const sf::Vector2f main_titles_size = {500, 40};
};


#endif

