#ifndef TABLE_H
#define TABLE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../state/gpstate.h"
#include "../cue.h"
#include "../ball.h"
#include "pocket.h"
#include "tablewall.h"
#include "unordered_map"
#include "../collider.h"


// Usato per tenere traccia dello stato delle palline dentro la mappa in Table()
struct BallStatus {
    BallStatus(Ball b) : ball(b), pocket(nullptr) {}
    Ball ball;
    Pocket* pocket;
};

class Table {
public:
    Table(sf::Vector2u window_size, sf::Vector2i offsets);
    void draw(sf::RenderWindow& window, GameplayState currentGS);
    Cue cue;
    void update(sf::Time time);
    const float REAL_TABLE_WIDTH = 2.84; // metri
    const float REAL_TABLE_HEIGHT = 1.42;
    std::vector<Collider*> getColliders();
private:
    sf::Vector2f offset; // Posizione del tavolo rispetto il viewport
    float frictionDeceleration = 50.3f; // Coefficiente di attrito
    sf::RectangleShape shape;
    std::vector<Pocket> pockets; // Buche
    std::vector<TableWall> walls; // Muri
    std::unordered_map<unsigned, BallStatus> balls;
    std::vector<Collider*> colliders;
};

#endif
