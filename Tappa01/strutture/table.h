#ifndef TABLE_H
#define TABLE_H
#include "ball.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PocketView {
public:
    PocketView();
    ~PocketView() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position; // Rispetto al tavolo
    sf::CircleShape shape;
    sf::Texture texture;
};

class Pocket { // Buca
public:
    Pocket(unsigned id);
    ~Pocket() = default;
    void draw(sf::RenderWindow& window);

private:
    PocketView view;
};

class TableView {
public:
    TableView();
    ~TableView() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    sf::RectangleShape shape;
    sf::Texture texture;
};

class Table {
public:
    Table();
    ~Table() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f offset;
    TableView view;
    std::vector<Pocket> pockets;
    std::vector<Ball> smooth;
    std::vector<Ball> striped;
    Ball black;
    Ball white;
};

#endif