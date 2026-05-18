#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include "../structures/cue.h"

enum Gamemode {
    SINGLE_PLAYER,
    MULTI_PLAYER
};


struct GameConfig {
    Gamemode gamemode = MULTI_PLAYER;
    CueType cuetype = CueType::FREE;
    unsigned int MAX_PLAYER_MISTAKES = 3;
    // Modalità a difficolta aumentata: mani tremolanti, aggiunge una velocità casuale diagonale tra -max_shakings_hands_speed e +max_shakings_hands_speed
    bool shaking_hands_mode = false;
    int max_shakings_hands_speed = 100;
    // Modalità a difficolta aumentata: masse di palline e stecca distorte casualmente nel range -max_mass_distorsions_grams e +max_mass_distorsions_grams
    bool weird_masses_mode = true;
    int max_mass_distorsions_grams = 1000; // In grammi
    const unsigned MAX_SHOT_SPEED = 1200;
    const unsigned MIN_SHOT_SPEED = 5;
    std::string to_string();
};


#endif
