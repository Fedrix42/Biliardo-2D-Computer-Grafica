#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

float dist(sf::Vector2f p1, sf::Vector2f p2);
float dist(sf::Vector2i p1, sf::Vector2f p2);
float dist(sf::Vector2i p1, sf::Vector2i p2);
float norm(sf::Vector2f v);

sf::Vector2f opposite(sf::Vector2f v);
sf::Vector2f clkwise_rot(sf::Vector2f v);
sf::Vector2f counterclkwise_rot(sf::Vector2f v);

std::string point_to_str(sf::Vector2f p);

#endif
