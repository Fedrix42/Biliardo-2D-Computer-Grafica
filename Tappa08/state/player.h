#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    std::string name;
    unsigned int remaining;
    unsigned int mistakes = 0; // Numero di falli effettuati
    std::string to_string();
    bool smooth = true; // Vero se deve imbucare le palline piene, falso se deve imbucare le rigate
};

#endif
