#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include "../structures/cue.h"

enum Gamemode {
    SINGLE_PLAYER,
    MULTI_PLAYER
};


struct GameConfig {
    Gamemode gamemode = SINGLE_PLAYER;
    CueType cuetype = CueType::ANCHOR;
    unsigned int MAX_PLAYER_MISTAKES = 3;
};


#endif
