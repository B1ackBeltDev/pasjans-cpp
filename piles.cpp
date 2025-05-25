#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "piles.hpp"
#include "cards.hpp"
#include "move.hpp"

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

    this->reservePile.insertCards(this->cardsManager->getAllCards());
}

void ReservePile::insertCards(std::vector<Card> cards){
    this->hiddenCards= cards;
}

bool PilesManager::makeMoveAction(MoveAction &action){
    if(!this->sPiles[action.fromPile-1].validateMoveFrom(action)){
        std::cout << "[SYSTEM] Validation from failed!" << std::endl;
        return false;   
    }

    if(!this->sPiles[action.toPile-1].validateMoveTo(action)){
        std::cout << "[SYSTEM] Validation to failed!" << std::endl;
        return false;
    }

    this->sPiles[action.fromPile-1].performMoveFrom(action);
    this->sPiles[action.toPile-1].performMoveTo(action);

    return true;
}

bool StandardPile::validateMoveFrom(MoveAction &action){
    if(action.howManyCards > this->revealdCount)
        return false;

    if(action.howManyCards == this->revealdCount && this->cards.size() - action.howManyCards > 0)
        action.revealdNew = true;

    int n = this->cards.size();
    for(int i = 0; i < action.howManyCards; i++)
        action.cards.push_back(this->cards[n-action.howManyCards+i]);

    return true;
}

bool StandardPile::validateMoveTo(MoveAction &action){
    if(this->cards.size() == 0){
        // The pile is empty
        if(action.cards[0].getRank() != Ranks::KING)
            return false;
    }else{
        // The pile is not empty
        if(this->cards.back().getColor() == action.cards[0].getColor())
            return false;
        if(static_cast<int>(this->cards.back().getRank()) - static_cast<int>(action.cards[0].getRank()) != 1)
            return false;
    }
    return true;
}

void StandardPile::performMoveFrom(MoveAction &action){
    for(int i = 0; i < action.howManyCards; i++)
        this->cards.pop_back();
    this->revealdCount -= action.howManyCards;
    if(action.revealdNew)
        this->revealdCount = 1;
}

void StandardPile::performMoveTo(MoveAction &action){
    for(int i = 0; i < action.howManyCards; i++)    
        this->cards.push_back(action.cards[i]);
    this->revealdCount += action.howManyCards;
}

bool ReservePile::validateDrawAction(DrawAction &action){
    if(this->revealdCards.empty())
        return false;
    action.card = this->revealdCards.back();
    return true;
}

void ReservePile::performDrawAction(DrawAction &action){
    this->revealdCards.pop_back();
}

bool StandardPile::validateDrawAction(DrawAction &action){
    if(this->cards.empty()){
        if(action.card.getRank() != Ranks::KING)
            return false;
    }else {
        if(this->cards.back().getColor() == action.card.getColor())
            return false;
        if(static_cast<int>(this->cards.back().getRank()) - static_cast<int>(action.card.getRank()) != 1)
            return false; 
    }
    return true;
}

void StandardPile::performDrawAction(DrawAction &action){
    this->cards.push_back(action.card);
    this->revealdCount++;
}

bool PilesManager::makeDrawAction(DrawAction &action){
    if(!this->reservePile.validateDrawAction(action))
        return false;
    if(!this->sPiles[action.toPile-1].validateDrawAction(action))
        return false;
    this->reservePile.performDrawAction(action);
    this->sPiles[action.toPile-1].performDrawAction(action);
    return true;
}

bool PilesManager::makeNewReserveAction(NewReserveAction &action){
    return this->reservePile.performNewReserveAction(action);
}

bool ReservePile::performNewReserveAction(NewReserveAction &action){
    if(this->revealdCards.empty() && this->hiddenCards.empty())
        return false;
    action.revealdCards = this->revealdCards;
    action.hiddenCards = this->hiddenCards;
    if(this->hiddenCards.empty()){
        this->hiddenCards = this->revealdCards;
        this->revealdCards.clear();

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(this->hiddenCards.begin(), this->hiddenCards.end(), g);
    }
    this->revealdCards.push_back(this->hiddenCards.back());
    this->hiddenCards.pop_back();
    return true;
}

bool PilesManager::makeAnswerAction(AnswerAction &action){
    if(action.fromReserve){ // from reserve
        if(!this->reservePile.validateAnswerAction(action))
            return false;
    }else{
        if(!this->sPiles[action.fromPile-1].validateAnswerAction(action))
            return false;
    }

    if(!this->resPiles[static_cast<int>(action.card.getSuit())].validateAnswerAction(action))
        return false;
    this->resPiles[static_cast<int>(action.card.getSuit())].performAnswerAction(action);

    if(action.fromReserve){ // from reserve
        this->reservePile.performAnswerAction(action);
    }else{
        this->sPiles[action.fromPile-1].performAnswerAction(action);
    }

    return true;
}

bool StandardPile::validateAnswerAction(AnswerAction &action){
    if(this->revealdCount == 0)
        return false;
    if(this->cards.size() - 1 > 0)
        action.revealdNew = true;
    action.card = this->cards.back();
    return true;
}

void StandardPile::performAnswerAction(AnswerAction &action){
    this->cards.pop_back();
    if(!action.revealdNew)
        this->revealdCount--;
}

bool ReservePile::validateAnswerAction(AnswerAction &action){
    if(this->revealdCards.empty())
        return false;
    action.card = this->revealdCards.back();
    return true;
}

void ReservePile::performAnswerAction(AnswerAction &action){
    this->revealdCards.pop_back();
}

bool ResultPile::validateAnswerAction(AnswerAction &action){
    if(this->cards.empty())
        return true;
    return (static_cast<int>(action.card.getRank()) - static_cast<int>(this->cards.back().getRank()) == 1);
}

void ResultPile::performAnswerAction(AnswerAction &action){
    this->cards.push_back(action.card);
}

bool PilesManager::checkEnd(){
    for(int i = 0; i < this->resPiles.size(); i++){
        if(this->resPiles[i].getCards()->empty() || this->resPiles[i].getCards()->back().getRank() != Ranks::KING)
            return false;
    }
    return true;
}