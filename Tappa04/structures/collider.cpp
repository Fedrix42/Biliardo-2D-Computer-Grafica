#include "collider.h"
#include "../utils.h"
#include <iostream>

void rollbackPositions(Collider* c1, Collider* c2, sf::Vector2f c1p, sf::Vector2f c2p){
    c1->setPosition(c1p);
    c2->setPosition(c2p);
}

std::vector<Collision> Collider::computeCollisions(Collider* collider)
{
    std::vector<Collision> result;
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

                sf::Vector2f A = my_bounds.at(i);
                sf::Vector2f B = my_bounds.at( i+ 1);
                sf::Vector2f C = other_bounds.at(j);
                sf::Vector2f D = other_bounds.at(j + 1);

                std::optional<sf::Vector2f> impact_point = segment_intersection(A, B, C, D);

                if(impact_point){
                    sf::Vector2f my_segment = B - A;
                    sf::Vector2f collider_segment = D - C;
                    sf::Vector2f my_normal = clkwise_rot(my_segment) / norm(my_segment); // Perpendiolare al segmento B - A
                    sf::Vector2f collider_normal = clkwise_rot(collider_segment) / norm(collider_segment);

                    result.resize(2);
                    result.at(0) = Collision{ // Aggiungi la collisione a me
                        my_normal,
                        *impact_point,
                        this->getPosition()
                    };
                    result.at(1) = Collision{ // Aggiungi la collisione al collider
                        collider_normal,
                        *impact_point,
                        collider->getPosition()
                    };
                }
            }
        }

        // Incremento la posizione per la velocità normalizzata
        this->setPosition(this->getPosition() + my_speed_norm);
        collider->setPosition(collider->getPosition() + collider_speed_norm);
    }
    rollbackPositions(this, collider, my_old_position, other_old_position); // Importante: devo fare il rollback delle posizioni originali
    return result;
}



float Collider::velocityAlongNormal(Collider* collider) const
{
    auto it = collisions.find(collider);
    if(it != collisions.end()){
        return dot(getSpeed(), it->second.normal);
    }else {
        throw std::logic_error("[ERROR] No collision with collider");
    }

}


bool Collider::doesBoundBoxesCollide(Collider* collider)
{
    return this->getBoundBox().findIntersection(collider->getBoundBox()) != std::nullopt;
}

