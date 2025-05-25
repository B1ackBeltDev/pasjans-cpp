#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "piles.hpp"
#include "cards.hpp"
#include "game.hpp"
#include "move.hpp"
#include <string>
#include <cstdlib>
#include <windows.h>

void Game::start(){
    SetConsoleOutputCP(CP_UTF8);
    this->resetScreen(); 
    while(1){
        // this->resetScreen();
        this->getAction();
        if(this->checkEnd()){
            std::cout << "You have won! Congratulations!" << std::endl;
            exit(0);
        }
    }
}

bool Game::checkEnd(){
    return this->pilesManager.checkEnd();
}

// void Game::printBoard(){
//     std::vector<StandardPile>* sPiles = this->pilesManager.getSPiles();
//     std::vector<ResultPile>* resPiles = this->pilesManager.getResPiles();
//     ReservePile* reservePile = this->pilesManager.getReservePile();

//     // Print Reserve Cards
//     std::cout << "[RESERVE]" << std::endl;
//     std::cout << "Hidden count: " << reservePile->getHiddenCards()->size() << std::endl;
//     std::cout << "Reveald cards (from last): ";
//     if (reservePile->getRevealdCards()->size() == 0){
//         std::cout << "Empty";
//     }else {
//         for(Card& card : *reservePile->getRevealdCards()){
//             card.printCard();
//             std::cout << ' ';
//         }
//     }
//     std::cout << std::endl;
    
//     // Print Result Piles
//     std::cout << std::endl;
//     std::cout << "[RESULT PILES]" << std::endl;
//     for(int i = 0; i < resPiles->size(); i++){
//         std::cout << "Pile " << getSuitString((*resPiles)[i].getSuit()) << ": ";
//         // print last card
//         std::vector<Card> cards = *(*resPiles)[i].getCards();
//         if(cards.size() > 0){
//             for(Card card : cards){
//                 card.printCard();
//                 std::cout << ' ';
//             }
//         } else {
//             std::cout << "Empty";
//         }
//         std::cout << std::endl;
//     }

//     // Print Standard Piles
//     std::cout << std::endl;
//     std::cout << "[STANDARD PILES]" << std::endl;
//     for(int i = 0; i < sPiles->size(); i++){
//         std::cout << "Pile " << i+1 << ": ";
//         // print available cards and X for unavailable cards: unavailable cards are the first revealdCount cards
//         int n = (*sPiles)[i].getCards()->size();
//         int revealdCount = (*sPiles)[i].getRevealdCount();
//         for(int j = 0; j < n-revealdCount; j++){
//             std::cout << "X ";
//         }
//         for(int j = n-revealdCount; j < n; j++){
//             (*(*sPiles)[i].getCards())[j].printCard();
//             std::cout << ' ';
//         }
//         std::cout << std::endl;
//     }

//     std::cout << std::endl;
// }

void inject(std::vector<std::vector<std::string>> obj, int y, int x, std::vector<std::vector<std::string>> &screen){
    for(int dy = 0; dy < obj.size(); dy++){
        for(int dx = 0; dx < obj[dy].size(); dx++){
            screen[y+dy][x+dx] = obj[dy][dx];
        }
    }
}

void Game::printBoard(){
    std::vector<StandardPile> sPiles = *this->pilesManager.getSPiles();
    std::vector<ResultPile> resPiles = *this->pilesManager.getResPiles();
    ReservePile reservePile = *this->pilesManager.getReservePile();

    int cardWidth = 7;
    int cardHeight = 5;
    std::vector<std::vector<std::string>> screen(cardHeight+51+cardHeight, std::vector<std::string>(cardWidth*7, " "));


    std::vector<std::vector<std::string>> card = {{"╭","─","─","─","─","─","╮"},
                                                  {"│"," "," "," "," "," ","│"},
                                                  {"│"," "," "," "," "," ","│"},
                                                  {"│"," "," "," "," "," ","│"},
                                                  {"╰","─","─","─","─","─","╯"}};

    std::vector<std::vector<std::string>> dottedCard = {{"╭","╌","╌","╌","╌","╌","╮"},
                                                        {"┆"," "," "," "," "," ","┆"},
                                                        {"┆"," "," "," "," "," ","┆"},
                                                        {"┆"," "," "," "," "," ","┆"},
                                                        {"╰","╌","╌","╌","╌","╌","╯"}};

    // Inject Reserve Pile
    inject(card, 0, 0, screen);
    inject({{std::to_string(reservePile.getHiddenCards()->size()/10), std::to_string(reservePile.getHiddenCards()->size()%10)}}, 0, 2, screen);
    if(reservePile.getRevealdCards()->empty()){
        inject(dottedCard, 0, cardWidth, screen);
    }else{
        inject(card, 0, cardWidth, screen);
        inject({reservePile.getRevealdCards()->back().toVec()}, 0, cardWidth+2, screen);
    }
    inject({{"0"}}, 2, 3+cardWidth, screen);

    // Inject Answer Piles
    for(int i = 0; i < 4; i++){
        if(resPiles[i].getCards()->empty()) inject(dottedCard, 0, (i+3)*cardWidth, screen);
        else {
            inject(card, 0, (i+3)*cardWidth, screen);
            inject({resPiles[i].getCards()->back().toVec()}, 0, 2+(i+3)*cardWidth, screen);
        }
        inject({{getSuitString(resPiles[i].getSuit(), true)}}, 2, 3+(i+3)*cardWidth, screen);
    }

    // Inject Standard Piles
    for(int i = 0; i < 7; i++){
        if(sPiles[i].getCards()->empty()){
            inject(dottedCard, cardHeight, i*cardWidth, screen);
            inject({{std::to_string(i+1)}}, 2+cardHeight, 3+i*cardWidth, screen);
            continue;
        }
        for(int j = 0; j < sPiles[i].getCards()->size() - sPiles[i].getRevealdCount(); j++){
            inject({card[0], card[1]}, cardHeight+2*j, i*cardWidth, screen);
            //inject({sPiles[i].getCards()->at(j).toVec()}, cardHeight+2*j, 2+i*cardWidth, screen);
        }
        for(int j = sPiles[i].getCards()->size() - sPiles[i].getRevealdCount(); j < sPiles[i].getCards()->size() - 1; j++){
            inject({card[0], card[1]}, cardHeight+2*j, i*cardWidth, screen);
            inject({sPiles[i].getCards()->at(j).toVec()}, cardHeight+2*j, 2+i*cardWidth, screen);            
        }
        int j = sPiles[i].getCards()->size() - 1;
        inject(card, cardHeight+2*j, i*cardWidth, screen);
        inject({sPiles[i].getCards()->at(j).toVec()}, cardHeight+2*j, 2+i*cardWidth, screen);
        inject({{std::to_string(i+1)}}, 2+cardHeight+2*j, 3+i*cardWidth, screen);
    }

    // Print Board
    for(int y = 0; y < screen.size(); y++){
        bool allSpaces = true;
        for(int x = 0; x < screen[y].size(); x++){
            if(screen[y][x] != " "){
                allSpaces = false;
                break;
            }
        }
        if(allSpaces)
            break;
        for(int x = 0; x < screen[y].size(); x++){
            std::cout << screen[y][x];
        }
        std::cout << std::endl;
    }
}

void Game::resetScreen() {
    system("cls");
    this->printBoard();
    // this->testPrintBoard();
}

void Game::getAction() {
    std::cout << "Enter action type (move - 1, new reserve - 2, answer - 3, exit - 4): ";
    int actionType;
    std::cin >> actionType;

    if(!(actionType >= 1 && actionType <= 5)){
        this->resetScreen();
        std::cout << "[SYSTEM] Invalid action type!" << std::endl;
        // return false;
        return;
    }

    switch (actionType) {
        case 1: {
            // Get from pile
            this->resetScreen();
            int from;
            std::cout << "From which pile you want to move from (0-7): ";
            std::cin >> from;
            if(!(from >= 0 && from <= 7)){
                this->resetScreen();
                std::cout << "[SYSTEM] Invalid range of piles!" << std::endl;
                // return false;
                return;
            }

            if(from == 0){
                this->resetScreen();
                int to;
                std::cout << "To which pile you want to draw the card to (1-7): ";
                std::cin >> to;

                if(!(to >= 1 && to <= 7)){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Invalid range of piles!" << std::endl;
                    // return false;
                    return;
                }

                DrawAction newAction = DrawAction();
                newAction.toPile = to;

                if(!this->pilesManager.makeDrawAction(newAction)){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Invalid move parameters!" << std::endl;
                    // return false;
                    return;
                }
            }else{
                // Get to pile
                this->resetScreen();
                int to;
                std::cout << "To which pile you want to move to (1-7): ";
                std::cin >> to;
                if(!(to >= 1 && to <= 7)){
                    this-> resetScreen();
                    std::cout << "[SYSTEM] Invalid range of piles!" << std::endl;
                    // return false;
                    return;
                }
                if(to == from){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Cannot move from the same pile!" << std::endl;
                    // return false;
                    return;
                }
    
                // Get How many cards
                this->resetScreen();
                int howMany;
                std::cout << "How many cards you want to move: ";
                std::cin >> howMany;
    
                if(howMany <= 0){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Number of cards must be positive!" << std::endl;
                    // return false;
                    return;
                }
    
                MoveAction newAction = MoveAction();
                newAction.fromPile = from;
                newAction.toPile = to;
                newAction.howManyCards = howMany;
    
                if(!this->pilesManager.makeMoveAction(newAction)){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Invalid move parameters!" << std::endl;
                    // return false;
                    return;
                }
            }

            break;
        }
        case 2: {
            NewReserveAction newAction = NewReserveAction();
            if(!this->pilesManager.makeNewReserveAction(newAction)){
                this->resetScreen();
                std::cout << "[SYSTEM] Invalid parameters" << std::endl;
                // return false;
                return;
            }
            // std::cout << "[DEBUG] LOL" << std::endl;
            
            break;
        }
        case 3: {
            this->resetScreen();
            // std::cout << "Do you want to answer from reserve? (y, *): ";
            // char fromReserve;
            // std::cin >> fromReserve;

            AnswerAction newAction = AnswerAction();
            // if(fromReserve == 'y'){
            //     newAction.fromReserve = true;
            // }else{
            //     newAction.fromReserve = false;
            //     this->resetScreen();
                std::cout << "From which pile you want to answer (0, 7): ";
                int from;
                std::cin >> from;

                if(!(from >= 0 && from <= 7)){
                    this->resetScreen();
                    std::cout << "[SYSTEM] Number out of range!" << std::endl;
                    // return false;
                    return;
                }

                newAction.fromPile = from;
                newAction.fromReserve = (from == 0 ? true : false);
            // }

            if(!this->pilesManager.makeAnswerAction(newAction)){
                this->resetScreen();
                std::cout << "[SYSTEM] Invalid parameters!" << std::endl;
                // return false;
                return;
            }

            break;
        }
        case 4: {
            this->resetScreen();

            std::cout << "Are you sure you want to exit (y/*): ";
            char ans;
            std::cin >> ans;

            if(ans == 'y'){
                std::cout << "[SYSTEM] Exiting..." << std::endl;
                exit(0);
            }else {
                this->resetScreen();
                // return false;
                return;
            }
    
            break;
        }
    }

    this->resetScreen();
    // return true;
    return;
}