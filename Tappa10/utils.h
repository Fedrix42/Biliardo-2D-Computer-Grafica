#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

constexpr float PI = 3.14159265358979323846f;

namespace utils {

    namespace physics {
        float distanceOnTime(float speed, float deceleration, sf::Time delta);
        sf::Vector2f speedAfterTime(sf::Vector2f speed, float deceleration, sf::Time delta);
    }

    namespace monocollisions {
        // Calcolo della velocità finale di "A" in un urto elastico mono dimensionale
        float finalSpeed1D_ofA(float massA, float massB, float inspeedA, float inspeedB);
    }


    namespace geometry {
        // Restituisce null se non ci sono intersezioni o sono infinite
        std::optional<sf::Vector2f> segment_intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D);
    }



    namespace vectors_screen_space {
        float distance(sf::Vector2f p1, sf::Vector2f p2);
        float distance(sf::Vector2i p1, sf::Vector2f p2);
        float distance(sf::Vector2i p1, sf::Vector2i p2);
        float norm(sf::Vector2f v);


        sf::Vector2f opposite(sf::Vector2f v);
        sf::Vector2f clkwise_rot(sf::Vector2f v);
        sf::Vector2f counterclkwise_rot(sf::Vector2f v);
        sf::Vector2f rotate(const sf::Vector2f& v, float radians, bool clockwise);
        float dot(sf::Vector2f a, sf::Vector2f b); // Prodotto scalare tra vettori
    }


    std::string point_to_str(sf::Vector2f p);
    void debug(sf::Vector2f p);


}


#endif
