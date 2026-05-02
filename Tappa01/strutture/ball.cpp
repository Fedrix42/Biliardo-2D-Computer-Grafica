#include "ball.h"
#include "../assetmgr.h"

/*
Propozioni di un tavolo da biliardo: Width 2 : Height 1
Solitamente 284cm x 142cm con buche da 12.5cm
Palline da 6cm, quindi in proporzione la metà di una buca
*/

Ball::Ball(unsigned id, float pocket_radius)
{
    this->id = id;
    shape.setRadius(pocket_radius / 2);
    shape.setPosition({100, 100});
    shape.setTexture(AssetMGR::instance().get_ball_texture(id));
}

bool Ball::is_smooth(){
    return (id >= BallID::SMOOTH_START && id <= BallID::SMOOTH_STOP);
}

bool Ball::is_striped(){
    return (id >= BallID::STRIPED_START && id <= BallID::STRIPED_STOP);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
