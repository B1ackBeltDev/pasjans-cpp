#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "piles.hpp"
#include "cards.hpp"

StandardPile::StandardPile(int id){
    this->id = id;
}

void StandardPile::insertCard(Card card){
    this->cards.push_back(card);
}

PilesManager::PilesManager(CardsManager* cardsManager){
    this->cardsManager = cardsManager;

    for(int i = 1; i <= this->SPILES; i++){
        this->sPiles.push_back(StandardPile(i));
        for(int j = 0; j < i; j++){
            Card new_card = this->cardsManager->drawCard();
            this->sPiles.back().insertCard(new_card);
        }
    }

    for(int i = 1; i<= this->RPILES; i++){
        this->resPiles.push_back(ResultPile(static_cast<Suits>(i-1)));
    }

    this->reservePiles.insertCards(this->cardsManager->getAllCards());
}

void ReservePile::insertCards(std::vector<Card> cards){
    this->hiddenCards= cards;
}