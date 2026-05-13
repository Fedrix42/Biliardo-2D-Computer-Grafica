#include "pocket.h"
#include "../../assetmgr.h"

/*
Le buche sono in proporzione 11.36 volte meno l'altezza del tavolo
*/
Pocket::Pocket(unsigned int id, sf::Vector2f table_size, sf::Vector2f offset)
{
    this->id = id;
    shape.setTexture(AssetMGR::instance().table_pocket_texture());
    resize(table_size, offset);
}

void Pocket::resize(sf::Vector2f table_size, sf::Vector2f offset)
{
    shape.setRadius(table_size.y / 11.36 / 2);
    shape.setOrigin({ shape.getRadius(), shape.getRadius() });
    switch (id) {
    case 0:
        shape.setPosition({ shape.getRadius(), shape.getRadius() });
        break;
    case 1:
        shape.setPosition({table_size.x / 2.0f, shape.getRadius() });
        break;
    case 2:
        shape.setPosition({ table_size.x - shape.getRadius(), shape.getRadius() });
        break;
    case 3:
        shape.setPosition({ table_size.x - shape.getRadius(), table_size.y - shape.getRadius() });
        break;
    case 4:
        shape.setPosition({table_size.x / 2.0f, table_size.y - shape.getRadius() });
        break;
    case 5:
        shape.setPosition({ shape.getRadius(), table_size.y - shape.getRadius() });
        break;
    }
    shape.setPosition(shape.getPosition() + offset);
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
