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
    unsigned int MAX_PLAYER_MISTAKES = 10;
    std::string to_string();
};


#endif
