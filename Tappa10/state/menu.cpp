#include "menu.h"
#include <iostream>

Label::Label(sf::Font& font, std::string str, bool clickable) : text(font){
    this->clickable = clickable;
    border.setFillColor(sf::Color(160, 160, 160));
    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(3);
    text.setCharacterSize(20);
    text.setString(str);
    text.setFillColor(sf::Color::White);
}

void Label::set_size(sf::Vector2f size)
{
    border.setSize(size);
    text.setPosition(border.getPosition() + size - (text.getLocalBounds().size / 2.0f));
}

void Label::set_position(sf::Vector2f position)
{
    border.setPosition(position);
    auto bounds = text.getLocalBounds();
    text.setPosition(
        position +
        border.getSize() / 2.0f -
        sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f)
    );
}


sf::FloatRect Label::get_bounds()
{
    return border.getGlobalBounds();
}


bool Label::clicked(sf::Vector2i cursorpos)
{
    bool clicked = hover(cursorpos);
    state = (clicked) ? !state : state;
    return clicked;
}

bool Label::hover(sf::Vector2i cursorpos)
{
    bool hover = border.getGlobalBounds().contains({static_cast<float>(cursorpos.x), static_cast<float>(cursorpos.y)});
    if(clickable){
        border.setFillColor((hover) ? sf::Color(192, 192, 192) : sf::Color(160, 160, 160));
    }
    return hover;
}


void Label::draw(sf::RenderWindow& window)
{
    border.setOutlineColor((state) ? sf::Color::Green : sf::Color::Black);
    window.draw(border);
    window.draw(text);
}

OptionsBlock::OptionsBlock(sf::Font& font, std::string t, std::string l, std::string r) : title(font, t, false), left(font, l, true), right(font, r, true){
    title.set_size(title_size);
    left.set_size({title_size.x / 2.0f - margin.x / 2.0f, title_size.y});
    right.set_size({title_size.x / 2.0f - margin.x, title_size.y});
}


void OptionsBlock::set_position(sf::Vector2f position)
{
    title.set_position(position);
    left.set_position({position.x, position.y + title.get_bounds().size.y + margin.y});
    right.set_position({position.x + title.get_bounds().size.x / 2.0f + margin.x / 2.0f, position.y + title.get_bounds().size.y + margin.y});
}

sf::FloatRect OptionsBlock::get_bounds()
{
    auto title_pos = title.get_bounds().position;
    auto title_size = title.get_bounds().size;
    return sf::FloatRect(title_pos, {title_size.x, title_size.y + margin.y + left.get_bounds().size.y});
}

bool OptionsBlock::hover(sf::Vector2i cursorpos)
{
    return left.hover(cursorpos) || right.hover(cursorpos);
}

std::optional<bool> OptionsBlock::clicked(sf::Vector2i cursorpos)
{
    if(left.clicked(cursorpos)){
        return true;
    } else if(right.clicked(cursorpos)){
        return false;
    }
    return std::nullopt;
}

void OptionsBlock::draw(sf::RenderWindow& window)
{
    title.draw(window);
    left.draw(window);
    right.draw(window);
}


Menu::Menu(sf::Vector2u window_size) : font("./railway.ttf"),
    cue_opts(font, "Cue Options", "Free", "Anchor"),
    diff_opts(font, "Difficulty Options", "Shaking Hands Mode", "Masses Distorsion Mode"),
    single_player_option(font, "Single Player Mode", true),
    multi_player_option(font, "Double Player Mode", true),
    play_button(font, "Play", true)
{
    single_player_option.set_size(main_titles_size);
    multi_player_option.set_size(main_titles_size);
    play_button.set_size(main_titles_size);
    resize(window_size);
    // Defaults
    cue_opts.left.state = true;
    single_player_option.state = true;
}

void Menu::resize(sf::Vector2u size)
{
    float posx = static_cast<float>(size.x) / 2.0f - main_titles_size.x / 2.0f;
    float menu_height = cue_opts.get_bounds().size.y + diff_opts.get_bounds().size.y + (3 * main_titles_size.y) + 4 * YMARGIN;
    float posy = (size.y - menu_height)  / 2.0f;
    cue_opts.set_position({posx, posy});
    diff_opts.set_position({posx, cue_opts.get_bounds().position.y + cue_opts.get_bounds().size.y + YMARGIN});
    single_player_option.set_position({posx, diff_opts.get_bounds().position.y + diff_opts.get_bounds().size.y + YMARGIN});
    multi_player_option.set_position({posx, single_player_option.get_bounds().position.y + single_player_option.get_bounds().size.y + YMARGIN});
    play_button.set_position({posx, multi_player_option.get_bounds().position.y + multi_player_option.get_bounds().size.y + YMARGIN});
}


void Menu::draw(sf::RenderWindow& window)
{
    cue_opts.draw(window);
    diff_opts.draw(window);
    single_player_option.draw(window);
    multi_player_option.draw(window);
    play_button.draw(window);
}

void Menu::click_event(GameConfig* config, sf::Vector2i cursorpos)
{
    if(std::optional<bool> res = cue_opts.clicked(cursorpos)){
        if(*res){
            cue_opts.right.state = false;
            cue_opts.left.state = true;
            config->cuetype = FREE;
        } else {
            cue_opts.left.state = false;
            cue_opts.right.state = true;
            config->cuetype = ANCHOR;
        }
    } else if(std::optional<bool> res = diff_opts.clicked(cursorpos)){
        if(*res){
            config->shaking_hands_mode = diff_opts.left.state;
        } else {
            config->weird_masses_mode = diff_opts.right.state;
        }
    } else if(single_player_option.clicked(cursorpos)){
        config->gamemode = SINGLE_PLAYER;
        multi_player_option.state = false;
        single_player_option.state = true;
    } else if(multi_player_option.clicked(cursorpos)){
        config->gamemode = MULTI_PLAYER;
        single_player_option.state = false;
        multi_player_option.state = true;
    } else if(play_button.clicked(cursorpos)){
        active = false; // Disabilito il menù
    }

}

void Menu::hover(sf::Vector2i cursorpos)
{
    if(cue_opts.hover(cursorpos)) return;
    if(diff_opts.hover(cursorpos)) return;
    if(single_player_option.hover(cursorpos)) return;
    if(multi_player_option.hover(cursorpos)) return;
    if(play_button.hover(cursorpos)) return;
}
























