#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "piles.hpp"
#include "cards.hpp"
#include "game.hpp"
#include <string>
#include <cstdlib>

void Game::start() {
    std::cout << "Game has started!" << std::endl;
    this->printBoard();
}

void Game::printBoard(){
    system("cls");

    std::vector<StandardPile>* sPiles = this->pilesManager.getSPiles();
    std::vector<ResultPile>* resPiles = this->pilesManager.getResPiles();
    ReservePile* reservePile = this->pilesManager.getReservePiles();

    // Print Reserve Cards
    std::cout << "[RESERVE]" << std::endl;
    std::cout << "Hidden count: " << reservePile->getHiddenCards()->size() << std::endl;
    std::cout << "Reveald cards (from last): ";
    if (reservePile->getRevealdCards()->size() == 0){
        std::cout << "Empty";
    }else {
        for(Card& card : *reservePile->getRevealdCards()){
            card.printCard();
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    
    // Print Result Piles
    std::cout << std::endl;
    std::cout << "[RESULT PILES]" << std::endl;
    for(int i = 0; i < resPiles->size(); i++){
        std::cout << "Pile " << getSuitString((*resPiles)[i].getSuit()) << ": ";
        // print last card
        std::vector<Card>* cards = (*resPiles)[i].getCards();
        if(cards->size() > 0){
            cards->back().printCard();
        } else {
            std::cout << "Empty";
        }
        std::cout << std::endl;
    }

    // Print Standard Piles
    std::cout << std::endl;
    std::cout << "[STANDARD PILES]" << std::endl;
    for(int i = 0; i < sPiles->size(); i++){
        std::cout << "Pile " << i+1 << ": ";
        // print available cards and X for unavailable cards: unavailable cards are the first revealdCount cards
        int n = (*sPiles)[i].getCards()->size();
        int revealdCount = (*sPiles)[i].getRevealdCount();
        for(int j = 0; j < n-revealdCount; j++){
            std::cout << "X ";
        }
        for(int j = n-revealdCount; j < n; j++){
            (*(*sPiles)[i].getCards())[j].printCard();
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

void Game::resetScreen() {
    system("cls");
    this->printBoard();
}

bool Game::getAction() {
    std::cout << "Enter action type: (move - 1, draw - 2, answer - 3, exit - 4)" << std::endl;
    int actionType;
    std::cin >> actionType;

    if(!(actionType >= 1 && actionType <= 4)){
        this->resetScreen();
        std::cout << "[ERROR] Invalid action type!" << std::endl;
        return false;
    }

    switch (actionType) {
        case 1:
            
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            std::cout << ""
            break;
    }

    return true;
}