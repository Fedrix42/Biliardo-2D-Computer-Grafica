#ifndef SHOTSTATE_H
#define SHOTSTATE_H

struct ShotState {
    const float DEFAULT_SHOT_SPEED = 200;
    float shot_speed = DEFAULT_SHOT_SPEED;
    std::vector<Ball*> hitted_by;
    Ball tip_copy; // Necessario per una buona gestione della memoria
};

#endif
