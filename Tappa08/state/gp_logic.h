#ifndef GPLOGIC_H
#define GPLOGIC_H
#include "../structures/table/table.h"
#include "shotstate.h"
#include "player.h"
#include "panel.h"
#include "config.h"

/*
Gameplay Logic
Contiene le operazioni che si effettuano alla fine di ogni round per valutare lo stato attuale del gioco.
*/
namespace GameLogic {
    bool round(ShotState* ss, Table* table, Player* current, Player* other, Panel* panel, GameConfig* config); // Restituisce se il gioco è terminato
}
#endif

