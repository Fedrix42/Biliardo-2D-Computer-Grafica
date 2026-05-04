#include "table.h"
#include <iostream>
#include "../utils.h"

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
*/

Table::Table(sf::Vector2u window_size, sf::Vector2i offsets)
{
    // Tavolo
    shape.setSize({ static_cast<float>(window_size.x), static_cast<float>(window_size.y) });
    shape.setTexture(AssetMGR::instance().table_texture());
    // Buche
    for (unsigned id = 0; id < 6; id++) {
        pockets.emplace_back(Pocket(id, window_size));
    }
    // Muri
    for (unsigned id = 0; id < 6; id++) {
        sf::Vector2f direction;
        if(id == 0 || id == 1){
            direction = {0, 1};
        } else if(id == 2){
            direction = {-1, 0};
        } else if (id == 3 || id == 4){
            direction = {0, -1};
        } else {
            direction = {1, 0};
        }
        walls.emplace_back(TableWall(id, pockets.at((id + 1) % 6), pockets.at(id), direction));
    }
    float pocket_radius = pockets.at(0).getRadius();

    // Palline
    balls.insert({BallIDRange::WHITE, BallStatus(Ball(BallIDRange::WHITE, pocket_radius, frictionCoeff))});
    balls.insert({BallIDRange::BLACK, BallStatus(Ball(BallIDRange::BLACK, pocket_radius, frictionCoeff))});
    for (unsigned id = BallIDRange::SMOOTH_START; id <= BallIDRange::SMOOTH_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionCoeff))});
    }
    for (unsigned id = BallIDRange::STRIPED_START; id <= BallIDRange::STRIPED_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionCoeff))});
    }

    // Stecca
    cue.setAnchor(&balls.find(BallIDRange::WHITE)->second.ball);
}

void Table::draw(sf::RenderWindow& window, GameplayState currentGS)
{
    window.draw(shape);
    for (unsigned id = 0; id < 6; id++) {
        pockets.at(id).draw(window);
        walls.at(id).draw(window);
    }
    for(auto& entry : balls){
        entry.second.ball.draw(window);
    }
    if(currentGS != GameplayState::SIMULATION){
        cue.draw(window);
    }
}

void Table::update(sf::Time time){
    for(auto& entry : balls){
        entry.second.ball.update(time);
    }
}


/*
Le buche sono in proporzione 11.36 volte meno l'altezza del tavolo
*/
Pocket::Pocket(unsigned int id, sf::Vector2u table_size)
{
    this->id = id;
    shape.setRadius(table_size.y / 11.36 / 2);
    shape.setTexture(AssetMGR::instance().table_pocket_texture());
    shape.setOrigin({ shape.getRadius(), shape.getRadius() });
    switch (id) {
    case 0:
        shape.setPosition({ shape.getRadius(), shape.getRadius() });
        break;
    case 1:
        shape.setPosition({static_cast<float>(table_size.x / 2), shape.getRadius() });
        break;
    case 2:
        shape.setPosition({ table_size.x - shape.getRadius(), shape.getRadius() });
        break;
    case 3:
        shape.setPosition({ table_size.x - shape.getRadius(), table_size.y - shape.getRadius() });
        break;
    case 4:
        shape.setPosition({static_cast<float>(table_size.x / 2), table_size.y - shape.getRadius() });
        break;
    case 5:
        shape.setPosition({ shape.getRadius(), table_size.y - shape.getRadius() });
        break;
    }
}

void Pocket::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2f Pocket::getPosition()
{
    return shape.getPosition();
}

float Pocket::getRadius()
{
    return shape.getRadius();
}

TableWall::TableWall(unsigned id, Pocket left, Pocket right, sf::Vector2f direction)
{
    this->id = id;
    sf::Vector2f leftp = left.getPosition();
    sf::Vector2f rightp = right.getPosition();
    float leftr = left.getRadius();
    float rightr = right.getRadius();

    shape.setFillColor(sf::Color(183, 131, 9));
    shape.setPointCount(4);

    // Left
    sf::Vector2f shape_point0 = (opposite(direction) * leftr) + leftp;
    shape_point0 = shape_point0 + (clkwise_rot(direction) * leftr);

    sf::Vector2f shape_point1 = (clkwise_rot(direction) * leftr) + leftp;


    // Right
    sf::Vector2f shape_point2 = (counterclkwise_rot(direction) * rightr) + rightp;

    sf::Vector2f shape_point3 = (opposite(direction) * rightr) + rightp;
    shape_point3 = shape_point3 + (counterclkwise_rot(direction) * rightr);




    shape.setPoint(0, shape_point0);
    shape.setPoint(1, shape_point1);
    shape.setPoint(2, shape_point2);
    shape.setPoint(3, shape_point3);

    shape.setTexture(AssetMGR::instance().table_wall_texture());
    shape.setOrigin(shape.getPoint(0));
    shape.setPosition(shape.getPoint(0));
}

void TableWall::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
