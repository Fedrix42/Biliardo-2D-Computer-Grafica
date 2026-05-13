#ifndef PANEL_H
#define PANEL_H
#include <SFML/Graphics.hpp>

class Panel {
public:
    Panel(sf::Vector2u window_size);
    void resize(sf::Vector2u size);
    void draw(sf::RenderWindow& window);
    float getHeight();
    void setLeft(std::string gm);
    void setRight(std::string pl);
    void setMiddle(std::string sh);
private:
    sf::Font font;
    sf::Text left;
    sf::Text right;
    sf::Text middle;
    sf::RectangleShape background;
    const float xmargin = 5;
};


#endif

