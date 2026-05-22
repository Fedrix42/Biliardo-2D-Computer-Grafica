#include "table.h"
#include <iostream>
#include "../../utils.h"
#include "../../assetmgr.h"

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
*/

Table::Table(sf::Vector2f table_size, sf::Vector2f offset)
 : cue(table_size / 2.0f + offset){
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
    float pocket_radius = pockets.at(0).get_radius();
    balls.insert({BallIDRange::WHITE, BallStatus(Ball(BallIDRange::WHITE, pocket_radius, friction_deceleration, {0,0}))});
    balls.insert({BallIDRange::BLACK, BallStatus(Ball(BallIDRange::BLACK, pocket_radius, friction_deceleration, {0,0}))});

    for (unsigned id = BallIDRange::SMOOTH_START; id <= BallIDRange::SMOOTH_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, friction_deceleration,{0,0}))});
    }
    for (unsigned id = BallIDRange::STRIPED_START; id <= BallIDRange::STRIPED_STOP; id++) {
        balls.insert({id,BallStatus(Ball(id, pocket_radius, friction_deceleration, {0,0}))});
    }
    reset(); // Riposiziono le palline correttamente
    // Stecca
    cue.anchor = (&balls.find(BallIDRange::WHITE)->second.ball);
}

void Table::apply_config(GameConfig* config){
    cue.type = config->cuetype;
    cue.shaking_hands = config->shaking_hands_mode;
    cue.max_shakings_hands_speed = config->max_shakings_hands_speed;
    reset();
    if(config->weird_masses_mode){
        for(auto& entry : balls){
            float distortion = (rand() % config->max_mass_distorsions_grams);
            distortion /= 1000; // Converto da grammi a kg
            entry.second.ball.set_mass(Ball::DEFAULT_MASS + distortion);
        }
    }
}


void Table::reset(){
    sf::Vector2f triangle_center = shape.getPosition() + sf::Vector2f{
        (shape.getSize().x * (2.0f / 3.0f)),
        shape.getSize().y / 2.0f
    };
    auto it = balls.begin();
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i <= j; ++i) {
            if(it->second.ball.get_id() == BallIDRange::WHITE){
                reset_white();
                ++it;
            }
            std::cout << "Resetting Ball " << it->second.ball.get_id() << std::endl;
            it->second.pocket = nullptr;
            it->second.counted = false;
            it->second.ball.set_speed({0.0f, 0.0f});
            float x = i - j * 0.5f;
            float y = static_cast<float>(j);
            sf::Vector2f pos = {x, y};
            pos = utils::vectors_screen_space::counterclkwise_rot(pos); // Ruoto
            pos *= (2 * it->second.ball.get_radius() + 20); // Scalo per diametro + margine
            pos += triangle_center; // Traslo su triangolo
            it->second.ball.set_position(pos);
            ++it;
        }
    }
}

void Table::reset_white(){
    std::cout << "Resetting Ball " << BallIDRange::WHITE << std::endl;
    auto& wentry = balls.at(BallIDRange::WHITE);
    wentry.pocket = nullptr;
    wentry.counted = false;
    wentry.ball.set_speed({0.0f, 0.0f});
    auto& white = wentry.ball;
    white.set_position(shape.getPosition() + sf::Vector2f{
            shape.getSize().x / 3.0f,
            shape.getSize().y / 2.0f
        }
    );
    white.set_speed({0, 0});
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
    float pocketr = pockets.at(0).get_radius();
    for(auto& entry : balls){
        entry.second.ball.resize(
            {table_size.x / old_table_size.x, table_size.y / old_table_size.y},
            pocketr,
            shape.getPosition(),
            old_table_pos
        );
    }

}


void Table::draw(sf::RenderWindow& window)
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
    cue.draw(window);
}

void Table::update(sf::Time time){
    for(auto& entry : balls){
        if(entry.second.pocket == nullptr){
            for(Pocket p : pockets){
                // Controllo se la pallina entra in una buca, non aggiorno la posizione delle palline in buca
                if(utils::vectors_screen_space::distance(p.get_position(), entry.second.ball.get_position()) <= p.get_radius()){
                    entry.second.pocket = &p;
                } else {
                    entry.second.ball.update(time);
                }
            }
        }
    }

}

std::vector<Ball *> Table::get_balls_on_table()
{
    std::vector<Ball*> res;
    for(auto& entry : balls){
        if(entry.second.pocket == nullptr){
            res.push_back(&entry.second.ball);
        }
    }
    return res;
}

std::vector<TableWall *> Table::get_walls()
{
    std::vector<TableWall*> res;
    for (unsigned id = 0; id < 6; id++) {
        res.push_back(&walls.at(id));
    }
    return res;
}

void Table::put_in_pocket(unsigned int id)
{
    balls.at(id).pocket = &pockets.at(0);
}





