#include "table.h"
#include "../utils.h"
Pocket::Pocket(unsigned id)
{
}
void Pocket::draw(sf::RenderWindow& window) { }

Table::Table()
{
    this->view = TableView();
    this->pockets = std::vector<Pocket>();
    for (unsigned id = 0; id < 6; id++) {
        this->pockets.push_back(Pocket(id));
    }
    this->smooth = std::vector<Ball>();
    for (int id = BallID::SMOOTH_START; id <= BallID::SMOOTH_STOP; id++) {
        this->smooth.push_back(Ball(id));
    }
    this->striped = std::vector<Ball>();
    for (int id = BallID::STRIPED_START; id <= BallID::STRIPED_STOP; id++) {
        this->striped.push_back(Ball(id));
    }
    this->black = Ball(BallID::BLACK);
    this->white = Ball(BallID::WHITE);
}

void Table::draw(sf::RenderWindow& window)
{
    this->view.draw(window);
}

TableView::TableView()
{
    // this->texture = sf::Texture(ASSERT_FOLDER / "table.png");
    this->position = { 0, 0 };
    this->shape = sf::RectangleShape({ 200, 100 });
    // this->shape.setTexture(&this->texture);
    this->shape.setPosition(this->position);
}

void TableView::draw(sf::RenderWindow& window)
{
    window.draw(this->shape);
}

PocketView::PocketView()
{
}
