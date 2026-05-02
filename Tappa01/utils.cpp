#include "utils.h"

float dist(sf::Vector2f a, sf::Vector2f b){
	float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

#include <string>

std::string point_to_str(sf::Vector2f p){
    return "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
}
