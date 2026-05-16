#include "panel.h"

Panel::Panel(sf::Vector2u window_size)
: font("./railway.ttf"), left(font), right(font), middle(font)
{
    background.setFillColor(sf::Color(117,117,105));
    left.text.setFillColor(sf::Color::White);
    middle.text.setFillColor(sf::Color::White);
    right.text.setFillColor(sf::Color::White);
    resize(window_size);
}

void Panel::setLeft(std::string gm, bool blink)
{
    left.text.setString(gm);
    left.blink = blink;
}

void Panel::setRight(std::string pl, bool blink)
{
    right.text.setString(pl);
    right.blink = blink;
}

void Panel::setMiddle(std::string sh, bool blink)
{
    middle.text.setString(sh);
    middle.blink = blink;
}

void Panel::resize(sf::Vector2u size){
    background.setSize({static_cast<float>(size.x), static_cast<float>(size.y) / 20});

    left.text.setCharacterSize(background.getSize().y * 0.75f);
    left.text.setPosition({0 + xmargin, 0});

    middle.text.setCharacterSize(background.getSize().y * 0.75f);
    middle.text.setPosition({static_cast<float>(size.x) / 2 - (middle.text.getLocalBounds().size.x / 2.0f), 0});

    right.text.setCharacterSize(background.getSize().y * 0.75f);
    right.text.setPosition({static_cast<float>(size.x) - right.text.getLocalBounds().size.x - xmargin, 0});
}

float Panel::getHeight()
{
    return background.getSize().y;
}

void draw_l(sf::RenderWindow& window, Label l){
    if(l.blink){
        if(l.show){
            window.draw(l.text);
        }
        l.show = !l.show;
    } else {
        window.draw(l.text);
    }

}

void Panel::draw(sf::RenderWindow& window)
{
    window.draw(background);
    draw_l(window, left);
    draw_l(window, right);
    draw_l(window, middle);
}

