#ifndef TABLE_H
#define TABLE_H
#include "ball.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../assetmgr.h"
#include "cue.h"
#include "unordered_map"



class Pocket { // Buca
public:
    Pocket(unsigned id, sf::Vector2u table_size);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    float getRadius();

private:
    unsigned id;
    sf::CircleShape shape;
    std::vector<Ball*> balls;
};

class TableWall {
public:
    TableWall(unsigned id, Pocket left, Pocket right, sf::Vector2f direction);
    void draw(sf::RenderWindow& window);

private:
    unsigned id;
    sf::ConvexShape shape;
};


// Usato per tenere traccia dello stato delle palline dentro la mappa in Table()
struct BallStatus {
    BallStatus(Ball b) : ball(b), pocket(nullptr) {}
    Ball ball;
    Pocket* pocket;
};

class Table {
public:
    Table(sf::Vector2u window_size, sf::Vector2i offsets);
    void draw(sf::RenderWindow& window);
    Cue cue;
    void update(sf::Time time);
    const float REAL_TABLE_WIDTH = 2.84; // metri
    const float REAL_TABLE_HEIGHT = 1.42;
private:
    // Posizione del tavolo
    sf::Vector2f offset;
    // Textures usate (unico caricamento per tipo)
    sf::RectangleShape shape;
    std::vector<Pocket> pockets; // Buche
    std::vector<TableWall> walls; // Muri
    std::unordered_map<unsigned, BallStatus> balls;
};

#endif
