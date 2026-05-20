#include "panel.h"

Panel::Panel(sf::Vector2u window_size)
: font("./railway.ttf"),
    game_options(font),
    shot_speed_label(font),
    game_modes(font),
    curr_player_label(font),
    curr_player_indicator_label(font),
    other_player_label(font)
{
    // Colori
    background.setFillColor(sf::Color(117,117,105));
    game_options.setFillColor(sf::Color::White);
    shot_speed_label.setFillColor(sf::Color::White);
    game_modes.setFillColor(sf::Color::White);
    curr_player_label.setFillColor(sf::Color::White);
    other_player_label.setFillColor(sf::Color::White);
    curr_player_indicator_label.setFillColor(sf::Color::White);

    curr_player_indicator_label.setString("<-- Round of  |  Opponent -->");

    resize(window_size);

    // Dimensione del carattere
    unsigned int char_size = background.getSize().y * 0.5f *0.75f; // Il 75% della metà del pannello (altezza di un singolo livello)
    game_options.setCharacterSize(char_size);
    shot_speed_label.setCharacterSize(char_size);
    game_modes.setCharacterSize(char_size);
    curr_player_label.setCharacterSize(char_size);
    other_player_label.setCharacterSize(char_size);
    curr_player_indicator_label.setCharacterSize(char_size);

    this->window_size = window_size;
}

void Panel::setMessage(std::string msg)
{
    shot_speed_label.setString(msg);
    shot_speed_label.setPosition({static_cast<float>(window_size.x) / 2 - (shot_speed_label.getLocalBounds().size.x / 2.0f), 0});
}


void Panel::setShotSpeed(int speed)
{
    shot_speed_label.setString(std::to_string(speed) + " px / s");
    shot_speed_label.setPosition({static_cast<float>(window_size.x) / 2 - (shot_speed_label.getLocalBounds().size.x / 2.0f), 0});
}

void Panel::setGameMode(GameConfig* config)
{
    std::string game_modes_str = (config->cuetype == FREE) ? "Free Cue" : "Anchor Cue";
    game_modes_str += (config->shaking_hands_mode) ? " | Shaking Hands Mode" : "";
    game_modes_str += (config->weird_masses_mode) ? " | Masses Distorsion Mode" : "";
    game_modes.setString(game_modes_str);
    game_modes.setPosition({static_cast<float>(window_size.x) - game_modes.getLocalBounds().size.x - xmargin, 0});

    game_options.setString((config->gamemode == SINGLE_PLAYER) ? "Single Player" : "Dual Player");
}

void Panel::setCurrent(Player* current)
{
    curr_player_label.setString(current->to_string());
    curr_player_label.setPosition({0 + xmargin, background.getSize().y / 2.0f});
}

void Panel::setOther(Player* other)
{
    other_player_label.setString(other->to_string());
    other_player_label.setPosition({static_cast<float>(window_size.x) - other_player_label.getLocalBounds().size.x - xmargin, background.getSize().y / 2.0f});
}


void Panel::resize(sf::Vector2u size){
    background.setSize({static_cast<float>(size.x), PANEL_HEIGHT});

    // Posizionamento del livello superiore
    game_options.setPosition({0 + xmargin, 0});
    shot_speed_label.setPosition({static_cast<float>(size.x) / 2.0f - (shot_speed_label.getLocalBounds().size.x / 2.0f), 0});
    game_modes.setPosition({static_cast<float>(size.x) - game_modes.getLocalBounds().size.x - xmargin, 0});

    // Posizionamento del livello inferiore
    curr_player_label.setPosition({0 + xmargin, background.getSize().y / 2.0f});
    curr_player_indicator_label.setPosition({static_cast<float>(size.x) / 2.0f - (curr_player_indicator_label.getLocalBounds().size.x / 2.0f), background.getSize().y / 2.0f});
    other_player_label.setPosition({static_cast<float>(size.x) - other_player_label.getLocalBounds().size.x - xmargin, background.getSize().y / 2.0f});

    this->window_size = size;
}

float Panel::getHeight()
{
    return background.getSize().y;
}




void Panel::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(game_options);
    window.draw(shot_speed_label);
    window.draw(game_modes);
    window.draw(curr_player_label);
    window.draw(curr_player_indicator_label);
    window.draw(other_player_label);
}

