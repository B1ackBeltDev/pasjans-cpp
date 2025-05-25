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

public:
    Game() : pilesManager(&cardsManager) {};

    void start();
    void printBoard();
    // void testPrintBoard();
    void getAction();
    void resetScreen();
    bool checkEnd();
};