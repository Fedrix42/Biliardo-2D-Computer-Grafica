#include "tablewall.h"
#include "../../assetmgr.h"
#include "../../utils.h"

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

std::vector<sf::Vector2f> TableWall::getHitbox() const {
    std::vector<sf::Vector2f> res;
    for(int i = 0; i < 4; i++){
        res.push_back(shape.getPoint(i)); // P0 --> P1, P1 --> P2, P2 --> P3
        // Non metto da P3 --> P0 in quanto è sempre sul bordo esterno del tavolo e nessun oggetto può collidere con esso
    }
    return res;
}

sf::Vector2f TableWall::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f TableWall::getSpeed() const
{
    return {0, 0};
}

void TableWall::setPosition(sf::Vector2f pos){}

void TableWall::setSpeed(sf::Vector2f speed){}

std::string TableWall::to_string() const {
    return ("Wall["  + std::to_string(id) + " -- "
                     + point_to_str(getBoundBox().position)
                     + point_to_str(getBoundBox().size)
    + "]");
}

sf::FloatRect TableWall::getBoundBox() const
{
    return sf::FloatRect(shape.getPoint(3), shape.getPoint(1) - shape.getPoint(3));
}

float TableWall::getMass() const
{
    return 10000; // Massa molto grande (Non uso MAXFLOAT per evitare overflow)
}





