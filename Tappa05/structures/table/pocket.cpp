#include "pocket.h"
#include "../../assetmgr.h"

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
