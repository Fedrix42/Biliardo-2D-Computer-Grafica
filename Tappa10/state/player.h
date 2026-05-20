#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    std::string name;
    unsigned int remaining;
    bool smooth; // Vero se deve imbucare le palline piene, falso se deve imbucare le rigate
    unsigned int mistakes = 0; // Numero di falli effettuati
    std::string to_string(){
        std::string res = "[" + this->name + "] " + std::to_string(remaining) + " Remaining | " + std::to_string(this->mistakes) + " Mistakes";
        res.append((this->smooth) ? " | Smooth" : " | Striped");
        return res;
    };

};

#endif
