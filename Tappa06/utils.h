#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

// Operazioni di fisica
// Calcolo della velocità finale di "A" in un urto elastico mono dimensionale
float fnspeedA_1D(float massA, float massB, float inspeedA, float inspeedB);
float distanceOnTime(float speed, float deceleration, sf::Time delta);
sf::Vector2f speedAfterTime(sf::Vector2f speed, float deceleration, sf::Time delta);

// Operazioni geometriche (non vettoriali)
std::optional<sf::Vector2f> segment_intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D); // Restituisce null se non ci sono intersezioni o sono infinite


// Operazioni con vettori
float dist(sf::Vector2f p1, sf::Vector2f p2);
float dist(sf::Vector2i p1, sf::Vector2f p2);
float dist(sf::Vector2i p1, sf::Vector2i p2);
float norm(sf::Vector2f v);

constexpr float PI = 3.14159265358979323846f;
sf::Vector2f opposite(sf::Vector2f v);
sf::Vector2f clkwise_rot(sf::Vector2f v);
sf::Vector2f counterclkwise_rot(sf::Vector2f v);
sf::Vector2f rotate(const sf::Vector2f& v, float radians, bool clockwise);
float dot(sf::Vector2f a, sf::Vector2f b);

std::string point_to_str(sf::Vector2f p);
void debug(sf::Vector2f p);

#endif
