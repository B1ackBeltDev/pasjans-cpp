#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "piles.hpp"
#include "cards.hpp"
#include "move.hpp"

class Game {
private:
    CardsManager cardsManager;
    PilesManager pilesManager;
    ActionsManager actionsManager;

public:
    Game() : pilesManager(&cardsManager), actionsManager(&pilesManager) {};

    void start();
    void printBoard();
    // void testPrintBoard();
    void getAction();
    void resetScreen();
    bool checkEnd();
};