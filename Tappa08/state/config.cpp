#include "config.h"

std::string GameConfig::to_string()
{
    std::string res = "";
    switch(gamemode){
        case SINGLE_PLAYER:
            res.append("SINGLE_PLAYER");
            break;
        case MULTI_PLAYER:
            res.append("MULTI_PLAYER");
            break;
    }
    res.append(" | ");
    switch(cuetype){
        case FREE:
            res.append("FREE");
            break;
        case ANCHOR:
            res.append("ANCHOR");
            break;
    }
    res.append(" | Max Mistakes " + std::to_string(MAX_PLAYER_MISTAKES));
    return res;
}
