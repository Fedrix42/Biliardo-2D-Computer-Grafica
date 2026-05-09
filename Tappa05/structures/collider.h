#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

/*
L'interfaccia "collisore" permette di verificare se sta avvenendo una collisione
tra due oggetti e identificare il punto di impatto ed altre informazioni
*/
class Collider;

struct HitboxWalker {
    std::vector<sf::Vector2f> self_hitbox;
    std::vector<sf::Vector2f> collider_hitbox;
    size_t self_hb_size;
    size_t collider_hb_size;
    size_t i;
    size_t j;
    std::pair< sf::Vector2f, sf::Vector2f > self_segment();
    std::pair<sf::Vector2f, sf::Vector2f> collider_segment();
    bool hasNext() const;
    void step();
};

struct Collision {
    sf::Time collision_time;
    sf::Vector2f normal; // Perpendiolare e normalizzato al punto di impatto
    sf::Vector2f collision_point; // Punto di collisione
    bool applied = false;
};

class Collider {
public:
    virtual ~Collider() = default;
    // Core
    std::unordered_map<Collider*, Collision> collisions; //  Collisioni tra me e gli altri
    std::optional<std::pair<Collision, Collision>> computeCollisions(Collider* collider, sf::Time current_t); // Calcola il punto di impatto con "alta" precisione (costoso)
    bool doesBoundBoxesCollide(Collider* collider); // Calcola la possibile collisione in maniera economica tramite la bound box
    // Physics
    float velocityAlongNormal(Collider* collider) const; // Velocità lungo la direzione normale
    // Setter e getter
    virtual std::string to_string() const = 0;
    virtual sf::Vector2f getSpeed() const = 0;
    virtual sf::Vector2f getPosition() const = 0; // Posizione attuale
    virtual float getDecelleration() const = 0;
    virtual float getMass() const = 0;
    virtual void setSpeed(sf::Vector2f speed) = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
private:
    std::optional<std::pair<Collision, Collision>> checkSegmentIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D) const;
    virtual sf::FloatRect getBoundBox() const = 0;
    virtual std::vector<sf::Vector2f> getHitbox() const = 0;
};



#endif
