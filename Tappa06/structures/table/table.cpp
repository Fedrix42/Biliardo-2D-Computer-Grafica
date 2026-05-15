#include "table.h"
#include <iostream>
#include "../../utils.h"
#include "../../assetmgr.h"

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
*/

Table::Table(sf::Vector2f table_size, sf::Vector2f offset)
 : cue(table_size / 2.0f + offset)
{
    assert(table_size.x == table_size.y * 2);
    // Tavolo
    shape.setPosition(offset);
    shape.setSize(table_size);

    shape.setTexture(AssetMGR::instance().table_texture());
    // Buche
    for (unsigned id = 0; id < 6; id++) {
        Pocket pt = Pocket(id, table_size, offset);;
        pockets.emplace_back(pt);
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
        walls.emplace_back(TableWall(id, &pockets.at((id + 1) % 6), &pockets.at(id), direction));
    }

    // Palline costruite con ordine triangolare
    float pocket_radius = pockets.at(0).getRadius();
    balls.insert({BallIDRange::WHITE, BallStatus(Ball(BallIDRange::WHITE, pocket_radius, frictionDeceleration, {0,0}))});
    balls.insert({BallIDRange::BLACK, BallStatus(Ball(BallIDRange::BLACK, pocket_radius, frictionDeceleration, {0,0}))});

    for (unsigned id = BallIDRange::SMOOTH_START; id <= BallIDRange::SMOOTH_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionDeceleration,{0,0}))});
    }
    for (unsigned id = BallIDRange::STRIPED_START; id <= BallIDRange::STRIPED_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, frictionDeceleration, {0,0}))});
    }
    reset(); // Riposiziono le palline correttamente
    // Stecca
    cue.anchor = (&balls.find(BallIDRange::WHITE)->second.ball);
}

void Table::reset()
{
    sf::Vector2f triangle_center = shape.getPosition() + sf::Vector2f{
        (shape.getSize().x * (2.0f / 3.0f)),
        shape.getSize().y / 2.0f
    };
    auto it = balls.begin();
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i <= j; ++i) {
            it->second.pocket = nullptr;
            if(it->second.ball.getID() == BallIDRange::WHITE){
                it->second.ball.setPosition(
                    shape.getPosition() +
                    sf::Vector2f{
                        shape.getSize().x / 3.0f,
                        shape.getSize().y / 2.0f
                    }
                );
                ++it;
            }
            float x = i - j * 0.5f;
            float y = static_cast<float>(j);
            sf::Vector2f pos = {x, y};
            pos = counterclkwise_rot(pos);
            pos *= (2 * it->second.ball.getRadius() + 10);
            pos += triangle_center;
            it->second.ball.setPosition(pos);
            ++it;
        }
    }
}


void Table::resize(sf::Vector2f table_size, sf::Vector2f offset){
    assert(table_size.x == table_size.y * 2);
    auto old_table_size = shape.getSize();
    auto old_table_pos = shape.getPosition();
    shape.setPosition(offset);
    shape.setSize(table_size);

    for(Pocket& pocket : pockets){
        pocket.resize(table_size, offset);
    }
    for(TableWall& wall : walls){
        wall.resize();
    }
    float pocketr = pockets.at(0).getRadius();
    for(auto& entry : balls){
        entry.second.ball.resize(
            {table_size.x / old_table_size.x, table_size.y / old_table_size.y},
            pocketr,
            shape.getPosition(),
            old_table_pos
        );
    }

}


void Table::draw(sf::RenderWindow& window, GameplayState currentGS)
{
    window.draw(shape);
    for (unsigned id = 0; id < 6; id++) {
        pockets.at(id).draw(window);
        walls.at(id).draw(window);
    }
    for(auto& entry : balls){
        if(entry.second.pocket == nullptr){
            entry.second.ball.draw(window);
        }
    }
    if(currentGS != GameplayState::SIMULATION){
        cue.draw(window);
    }
}

void Table::update(sf::Time time){
    for(auto& entry : balls){
        if(entry.second.pocket == nullptr){
            for(Pocket p : pockets){
                // Controllo se la pallina entra in una buca, non aggiorno la posizione delle palline in buca
                if(dist(p.getPosition(), entry.second.ball.getPosition()) <= p.getRadius()){
                    entry.second.pocket = &p;
                } else {
                    entry.second.ball.update(time);
                }
            }
        }
    }

}

std::vector<Ball *> Table::getBallsOnTable()
{
    std::vector<Ball*> res;
    for(auto& entry : balls){
        if(entry.second.pocket == nullptr){
            res.push_back(&entry.second.ball);
        }
    }
    return res;
}

std::vector<TableWall *> Table::getWalls()
{
    std::vector<TableWall*> res;
    for (unsigned id = 0; id < 6; id++) {
        res.push_back(&walls.at(id));
    }
    return res;
}





