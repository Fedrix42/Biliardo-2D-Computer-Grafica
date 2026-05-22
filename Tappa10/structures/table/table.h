#ifndef TABLE_H
#define TABLE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "../cue.h"
#include "../ball.h"
#include "pocket.h"
#include "tablewall.h"
#include "unordered_map"
#include "../../collisions/collisions.h"
#include "../../state/config.h"

// Usato per tenere traccia dello stato delle palline dentro la mappa in Table()
struct BallStatus {
    BallStatus(Ball b) : ball(b), pocket(nullptr) {}
    Ball ball;
    Pocket* pocket;
    bool counted = false; // Ci dice se la pallina è già stata usata per i contaggi sul gameplay (usato da state.cpp)
};

class Table {
public:
    Table(sf::Vector2f table_size, sf::Vector2f offset);
    void draw(sf::RenderWindow& window);
    void resize(sf::Vector2f table_size, sf::Vector2f offset);
    void apply_config(GameConfig* config);
    Cue cue;
    void update(sf::Time time);
    const float REAL_TABLE_WIDTH = 2.84; // metri
    const float REAL_TABLE_HEIGHT = 1.42;
    void reset();
    void reset_white();
    std::vector<Ball*> get_balls_on_table();
    std::vector<TableWall*> get_walls();
    std::unordered_map<unsigned, BallStatus> balls;
    sf::Vector2f offset; // Posizione del tavolo rispetto il viewport
    void put_in_pocket(unsigned id); // Per il debug e testing
private:
    float friction_deceleration = 30.3f; // Coefficiente di attrito
    sf::RectangleShape shape;
    std::vector<Pocket> pockets; // Buche
    std::vector<TableWall> walls; // Muri
};

#endif
