#pragma once
#include <stdlib.h>
#include <vector>
#include "cards.hpp"
#include "move.hpp"

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

    // Draw Action
    bool validateDrawAction(DrawAction &action);
    void performDrawAction(DrawAction &action);

    // New Reserve Action
    bool performNewReserveAction(NewReserveAction &action);

    // Answer Action;
    bool validateAnswerAction(AnswerAction &action);
    void performAnswerAction(AnswerAction &action);
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

    bool validateAnswerAction(AnswerAction &action);
    void performAnswerAction(AnswerAction &action);
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

    // Move Action
    bool validateMoveTo(MoveAction &action);
    bool validateMoveFrom(MoveAction &action);
    void performMoveTo(MoveAction &action);
    void performMoveFrom(MoveAction &action);
    // void undoMoveTo(MoveAction &action);
    // void undoMoveFrom(MoveAction &action);

    // Draw Action
    bool validateDrawAction(DrawAction &action);
    void performDrawAction(DrawAction &action);

    // Answer Action
    bool validateAnswerAction(AnswerAction &action);
    void performAnswerAction(AnswerAction &action);
};

class PilesManager {
private:
    const int SPILES = 7;
    const int RPILES = 4;

    CardsManager* cardsManager;

    std::vector<StandardPile> sPiles;
    std::vector<ResultPile> resPiles;
    ReservePile reservePile;

public:
    PilesManager(CardsManager* cardManager);

    std::vector<StandardPile>* getSPiles(){
        return &this->sPiles;
    }

    std::vector<ResultPile>* getResPiles(){
        return &this->resPiles;
    }

    ReservePile* getReservePile(){
        return &this->reservePile;
    }

    bool makeMoveAction(MoveAction &action);
    bool makeDrawAction(DrawAction &action);
    bool makeNewReserveAction(NewReserveAction &action);
    bool makeAnswerAction(AnswerAction &action);
    bool checkEnd();
};