#ifndef PANEL_H
#define PANEL_H
#include <SFML/Graphics.hpp>

struct Label {
    Label(sf::Font& font) : text(font){};
    sf::Text text;
    bool blink;
    bool show = true;
};

class Panel {
public:
    Panel(sf::Vector2u window_size);
    void resize(sf::Vector2u size);
    void draw(sf::RenderWindow& window);
    float getHeight();
    void setLeft(std::string gm, bool blink = false);
    void setRight(std::string pl, bool blink = false);
    void setMiddle(std::string sh, bool blink = false);
private:
    sf::Font font;
    Label left;
    Label right;
    Label middle;
    sf::RectangleShape background;
    const float xmargin = 5;
};


#endif

