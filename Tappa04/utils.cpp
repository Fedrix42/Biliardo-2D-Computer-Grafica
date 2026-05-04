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



// Altro

std::string point_to_str(sf::Vector2f p){
    return "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
}
