#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.hpp"

int main(){
    srand(time(NULL));

    Game game;
    game.start();

    return 0;
}