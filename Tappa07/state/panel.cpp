#include "panel.h"

Panel::Panel(sf::Vector2u window_size)
: font("./railway.ttf"), left(font), right(font), middle(font)
{
    background.setFillColor(sf::Color(117,117,105));
    left.setFillColor(sf::Color::White);
    middle.setFillColor(sf::Color::White);
    right.setFillColor(sf::Color::White);
    resize(window_size);
    this->window_size = window_size;
}

void Panel::setLeft(std::string gm)
{
    left.setString(gm);
    left.setPosition({0 + xmargin, 0});
}

void Panel::setRight(std::string pl)
{
    right.setString(pl);
    right.setPosition({static_cast<float>(window_size.x) - right.getLocalBounds().size.x - xmargin, 0});
}

void Panel::setMiddle(std::string sh)
{
    middle.setString(sh);
    middle.setPosition({static_cast<float>(window_size.x) / 2 - (middle.getLocalBounds().size.x / 2.0f), 0});
}

void Panel::resize(sf::Vector2u size){
    background.setSize({static_cast<float>(size.x), static_cast<float>(size.y) / 20});

    left.setCharacterSize(background.getSize().y * 0.75f);
    left.setPosition({0 + xmargin, 0});

    middle.setCharacterSize(background.getSize().y * 0.75f);
    middle.setPosition({static_cast<float>(size.x) / 2 - (middle.getLocalBounds().size.x / 2.0f), 0});

    right.setCharacterSize(background.getSize().y * 0.75f);
    right.setPosition({static_cast<float>(size.x) - right.getLocalBounds().size.x - xmargin, 0});
    this->window_size = size;
}

float Panel::getHeight()
{
    return background.getSize().y;
}



void Panel::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(left);
    window.draw(middle);
    window.draw(right);
}

