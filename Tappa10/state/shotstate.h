#ifndef SHOTSTATE_H
#define SHOTSTATE_H

struct ShotState {
    sf::Time shot_time;
    float shot_speed = 100;
    std::vector<Ball*> hitted_by;
    Ball tip_copy; // Necessario per una buona gestione della memoria
};

#endif
