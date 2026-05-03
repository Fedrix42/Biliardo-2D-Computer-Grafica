#include "utils.h"


float dist(sf::Vector2f p1, sf::Vector2f p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

float dist(sf::Vector2i p1, sf::Vector2f p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

float dist(sf::Vector2i p1, sf::Vector2i p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

float norm(sf::Vector2f v){
    return sqrt(pow(v.x,2) + pow(v.y,2));
}

// Rotazione di 180 gradi
sf::Vector2f opposite(sf::Vector2f v){
    return {-v.x, -v.y};
}

// Rotazione orario di 90 gradi rispetto all'origine e con asse y invertita (cresce verso il basso)
sf::Vector2f clkwise_rot(sf::Vector2f v){
    return {-v.y, v.x};
}

// Rotazione antioraria di 90 gradi rispetto all'origine e con asse y invertita (cresce verso il basso)
sf::Vector2f counterclkwise_rot(sf::Vector2f v){
    return {v.y, -v.x};
}

std::string point_to_str(sf::Vector2f p){
    return "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
}
