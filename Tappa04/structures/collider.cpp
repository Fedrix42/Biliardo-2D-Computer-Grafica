#include "collider.h"
#include "../utils.h"
#include <iostream>
std::optional<sf::Vector2f> Collider::collision_point(Collider* collider)
{
    /*  Normalizziamo la velocità di entrambi gli oggetti in modo da muoverli con una precisione molto alta
        e troviamo il primo punto di collisione. Se non ci sono punti di collisione tra la posizione attuale e
        quella futura, allora restituisco nullopt.
    */
    sf::Vector2f my_old_position = this->getPosition();
    sf::Vector2f other_old_position = collider->getPosition();

    // Normalizzo le velocità, in questo modo la loro norma è 1 e ho una precisione di 1 pixel
    auto my_speed_norm = (norm(this->getSpeed()) != 0) ? this->getSpeed() / norm(this->getSpeed()) : sf::Vector2f{0, 0};
    auto collider_speed_norm = (norm(collider->getSpeed()) != 0) ? collider->getSpeed() / norm(collider->getSpeed()) : sf::Vector2f{0, 0};

    // Posizione massima al prossimo frame, non tiene conto della decellerazione
    auto my_expected_max_position_next_frame = this->getPosition() + this->getSpeed();
    auto collider_expected_max_position_next_frame = collider->getPosition() + collider->getSpeed();

    while(norm(this->getPosition() - my_expected_max_position_next_frame) > 2 || norm(collider->getPosition() - collider_expected_max_position_next_frame) > 2){
        // Controllo se c'è un punto di collisione tra le hitbox
        std::vector<sf::Vector2f> my_bounds = this->getHitbox();
        std::vector<sf::Vector2f> other_bounds = collider->getHitbox();
        for(size_t i = 0; i < my_bounds.size() - 1; i++){
            for(size_t j = 0; j < other_bounds.size() - 1; j++){
                std::optional<sf::Vector2f> impact_point = segment_intersection(my_bounds.at(i), my_bounds.at(i + 1), other_bounds.at(j), other_bounds.at(j + 1));
                if(impact_point){
                    this->setPosition(my_old_position); // Importante: il rollback delle posizioni originali
                    collider->setPosition(other_old_position);
                    return impact_point;
                }
            }
        }

        // Incremento la posizione per la velocità normalizzata
        this->setPosition(this->getPosition() + my_speed_norm);
        collider->setPosition(collider->getPosition() + collider_speed_norm);
    }
    // Importante: il rollback delle posizioni originali
    this->setPosition(my_old_position);
    collider->setPosition(other_old_position);
    return std::nullopt;
}

bool Collider::doesBoundBoxesCollide(Collider* collider)
{
    return this->getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

