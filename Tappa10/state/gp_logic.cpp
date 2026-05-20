#include "gp_logic.h"


bool increase_mistakes(Player* current, Panel* panel, GameConfig* config){
    current->mistakes++;
    panel->setCurrent(current);
    if(current->mistakes >= config->MAX_PLAYER_MISTAKES){
        panel->setMessage("Alice, you lost! To many mistakes...");
        return true;
    }
    return false;
}


bool GameLogic::round(ShotState* ss, Table* table, Player* current, Player* other, Panel* panel, GameConfig* config){
    size_t hitted_size = ss->hitted_by.size();
    if(hitted_size == 0) return false;
    std::vector<Ball*> now_putted_in_pockets;

    /*
        Estrazione delle palline messe in buca dal giocatore corrente
    */
    for(unsigned int i = BallIDRange::TOTAL_START; i <= BallIDRange::TOTAL_STOP; ++i){
        auto& entry = table->balls.at(i);
        if(entry.pocket != nullptr && !entry.counted){
            now_putted_in_pockets.push_back(&entry.ball);
            entry.counted = true;
        }
    }


    /*
        Verifica dei falli
        Controllo che non ha colpito più una 1 pallina oppure ha colpito 1 pallina che non è la bianca
    */
    if(hitted_size > 1 || ss->hitted_by.at(0)->get_id() != BallIDRange::WHITE){
        if(increase_mistakes(current, panel, config)) return true;
    }
    ss->hitted_by = std::vector<Ball*>();


    /*
        Statistiche sulle palline messe in buca
    */
    bool white_in_pocket = false;
    bool black_in_pocket = false;
    unsigned smooth_in_pockets = 0;
    unsigned striped_in_pockets = 0;

    for(Ball* putted : now_putted_in_pockets){
        if(putted->get_id() == BallIDRange::BLACK){
            black_in_pocket = true;
        } else if(putted->get_id() == BallIDRange::WHITE){
            white_in_pocket = true;
        } else if(putted->is_smooth()){
            smooth_in_pockets++;
        } else if(putted->is_striped()){
            striped_in_pockets++;
        }
    }

    // Verifica della messa in buca della bianca
    if(white_in_pocket){
        if(increase_mistakes(current, panel, config)) return true;
        table->reset_white();
    }

    /*
        Conteggio dei punti e verifica dei falli con pallina nera
    */
    if(config->gamemode == SINGLE_PLAYER){
        unsigned points = smooth_in_pockets + striped_in_pockets;
        current->remaining -= points;
    } else {
        if(current->smooth){
            current->remaining -= smooth_in_pockets;
            other->remaining -= striped_in_pockets;
        } else {
            current->remaining -= striped_in_pockets;
            other->remaining -= smooth_in_pockets;
        }
    }
    panel->setCurrent(current);
    panel->setOther(other);

    /*
        Verifica della vittoria
    */
    if(black_in_pocket){
        if(current->remaining > 0 || white_in_pocket){
            if(white_in_pocket){
                panel->setMessage(current->name + ", you LOST! You put the ball 8 in the pocket but also the white one...");
            } else {
                panel->setMessage(current->name + ", you LOST! You put the ball 8 in the pocket with remaining balls...");
            }
        } else {
            panel->setMessage(current->name + ", you WON!");
        }
        return true;
    }

    return false;
}
