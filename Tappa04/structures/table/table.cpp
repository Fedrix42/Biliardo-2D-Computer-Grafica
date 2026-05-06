#include "table.h"
#include <iostream>
#include "../../utils.h"
#include "../../assetmgr.h"

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
    for(auto& wall : walls){
        colliders.push_back(&wall);
    }


    // Palline
    float pocket_radius = pockets.at(0).getRadius();
    balls.insert({BallIDRange::WHITE, BallStatus(Ball(BallIDRange::WHITE, pocket_radius, frictionCoeff))});

    for(auto& entry : balls){
        colliders.push_back(&entry.second.ball);
    }
    balls.insert({BallIDRange::BLACK, BallStatus(Ball(BallIDRange::BLACK, pocket_radius, frictionCoeff))});
    for (unsigned id = BallIDRange::SMOOTH_START; id <= BallIDRange::SMOOTH_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionCoeff))});
    }
    for (unsigned id = BallIDRange::STRIPED_START; id <= BallIDRange::STRIPED_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionCoeff))});
    }

    /* Tutte le palline sono colliders
    for(auto& entry : balls){
        colliders.push_back(&entry.second.ball);
    } */

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

std::vector<Collider *> Table::getColliders()
{
    return colliders;
}


