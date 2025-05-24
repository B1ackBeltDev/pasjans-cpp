#pragma once
#include <stdlib.h>
#include <vector>
#include "cards.hpp"

class ReservePile {
private:
    std::vector<Card> hiddenCards;
    std::vector<Card> revealdCards;

public:
    void insertCards(std::vector<Card> cards);

    std::vector<Card>* getHiddenCards() {
        return &this->hiddenCards;
    }

    std::vector<Card>* getRevealdCards() {
        return &this->revealdCards;
    }
};

class ResultPile {
private:
    std::vector<Card> cards;
    Suits suit;

public:
    ResultPile(Suits suit) { 
        this->suit = suit;
    }

    Suits getSuit() {
        return this->suit;
    }

    std::vector<Card>* getCards() {
        return &this->cards;
    }
};

class StandardPile {
private:
    int id;
    int revealdCount = 1;
    std::vector<Card> cards;
public:
    StandardPile(int id);

    void insertCard(Card card);

    std::vector<Card>* getCards() {
        return &this->cards;
    }

    int getRevealdCount(){
        return this->revealdCount;
    }
};

class PilesManager {
private:
    const int SPILES = 7;
    const int RPILES = 4;

    CardsManager* cardsManager;

    std::vector<StandardPile> sPiles;
    std::vector<ResultPile> resPiles;
    ReservePile reservePiles;

public:
    PilesManager(CardsManager* cardManager);

    std::vector<StandardPile>* getSPiles(){
        return &this->sPiles;
    }

    std::vector<ResultPile>* getResPiles(){
        return &this->resPiles;
    }

    ReservePile* getReservePiles(){
        return &this->reservePiles;
    }
};