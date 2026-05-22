#include "tablewall.h"
#include "../../assetmgr.h"
#include "../../utils.h"

TableWall::TableWall(unsigned id, Pocket* left, Pocket* right, sf::Vector2f direction)
: direction(direction), left(left), right(right)
{
    this->id = id;
    shape.setFillColor(sf::Color(183, 131, 9));
    shape.setPointCount(4);
    shape.setTexture(AssetMGR::instance().table_wall_texture());
    resize();
}

void TableWall::resize()
{
    sf::Vector2f leftp = left->get_position();
    sf::Vector2f rightp = right->get_position();
    float leftr = left->get_radius();
    float rightr = right->get_radius();

    // Left
    sf::Vector2f shape_point0 = (utils::vectors_screen_space::opposite(direction) * leftr) + leftp;
    shape_point0 = shape_point0 + (utils::vectors_screen_space::clkwise_rot(direction) * leftr);

    sf::Vector2f shape_point1 = (utils::vectors_screen_space::clkwise_rot(direction) * leftr) + leftp;


    // Right
    sf::Vector2f shape_point2 = (utils::vectors_screen_space::counterclkwise_rot(direction) * rightr) + rightp;

    sf::Vector2f shape_point3 = (utils::vectors_screen_space::opposite(direction) * rightr) + rightp;
    shape_point3 = shape_point3 + (utils::vectors_screen_space::counterclkwise_rot(direction) * rightr);

    shape.setPoint(0, shape_point0);
    shape.setPoint(1, shape_point1);
    shape.setPoint(2, shape_point2);
    shape.setPoint(3, shape_point3);
    shape.setOrigin(shape.getPoint(0));
    shape.setPosition(shape.getPoint(0));

}


void TableWall::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

std::vector<sf::Vector2f> TableWall::get_hitbox() const {
    std::vector<sf::Vector2f> res;
    for(size_t i = 0; i < shape.getPointCount(); i++){
        res.push_back(shape.getPoint(i));
    }
    return res;
}

sf::Vector2f TableWall::get_position() const {
    return shape.getPosition();
}


std::string TableWall::to_string() const {
    return ("Wall["  + std::to_string(id) + " -- "
                     + utils::point_to_str(get_bound_box().position)
                     + utils::point_to_str(get_bound_box().size)
    + "]");
}

sf::FloatRect TableWall::get_bound_box() const
{
    return sf::FloatRect(shape.getPoint(3), shape.getPoint(1) - shape.getPoint(3));
}




