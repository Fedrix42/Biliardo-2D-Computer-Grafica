#include "utils.h"
// Fisica

/*
Calcolo della Final Speed di A date
le masse e velocità Iniziali di A e B,
per un urto elastico monodimensionale.

La formula si ottiene mettendo a sistema l'equazione di conservazione del moto
con quella di conservazione dell'energia cinetica.
*/
float fnspeedA_1D(float massA, float massB, float inspeedA, float inspeedB){
    float msum = massA + massB;
    float comp1 = ((massA - massB) / msum) * inspeedA;
    float comp2 = ((2*massB) / msum) * inspeedB;
    return comp1 + comp2;
}

// Moto uniformemente accelerato
float distanceOnTime(float speed, float deceleration, sf::Time delta){
    return (speed*delta.asSeconds()) + 0.5f*deceleration*pow(delta.asSeconds(), 2);
}


// Operazioni geometriche per le collisioni
std::optional<sf::Vector2f> segment_intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D){
    const float EPS = 1e-6f;

    // Segmento 1: A - B
    // Segmento 2: C - D
    float delta1 = B.x - A.x;
    float delta2 = B.y - A.y;
    float delta3 = D.x - C.x;
    float delta4 = D.y - C.y;
    float delta5 = C.x - A.x;
    float delta6 = C.y - A.y;

    float det = delta1*delta4 - delta2 * delta3;
    if(det < EPS){
        return std::nullopt; // Segmenti coincidono o paralleli
    }

    float parameter1 = ((delta5*delta4)-(delta6*delta3)) / det;
    float parameter2 = ((delta5*delta2)-(delta6*delta1)) / det;
    if(parameter1 > 1 || parameter2 > 1 || parameter1 < EPS || parameter2 < EPS)
        return std::nullopt; // Nessun punto di intersezione
    sf::Vector2f res = {A.x + parameter1*(B.x - A.x), A.y + parameter1*(B.y - A.y)};
    return res;
}



// Op. vettoriali
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


sf::Vector2f opposite(sf::Vector2f v){ // Rotazione di 180 gradi
    return {-v.x, -v.y};
}


sf::Vector2f clkwise_rot(sf::Vector2f v){ // Rotazione orario di 90 gradi rispetto all'origine e con asse y invertita (cresce verso il basso)
    return {-v.y, v.x};
}


sf::Vector2f counterclkwise_rot(sf::Vector2f v){ // Rotazione antioraria di 90 gradi rispetto all'origine e con asse y invertita (cresce verso il basso)
    return {v.y, -v.x};
}

sf::Vector2f rotate(const sf::Vector2f& v, float radians, bool clockwise) { // Rotazione generica di radianti, oraria o antioraria
    float angle = clockwise ? radians : -radians;

    float c = std::cos(angle);
    float s = std::sin(angle);

    return {
        v.x * c - v.y * s,
        v.x * s + v.y * c
    };
}

// Prodotto scalare (non trovato in SFML)
float dot(sf::Vector2f a, sf::Vector2f b){
    return a.x * b.x + a.y * b.y;
}



// Altro

std::string point_to_str(sf::Vector2f p){
    return "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
}
