#include "cards.hpp"
#include <iostream>
#include <string>
#include <windows.h>

std::string getSuitString(Suits suit) {
    switch (suit) {
        case Suits::HEARTS:
            return "♡";
            break;
        case Suits::SPADES:
            return "♠";
            break;
        case Suits::CLUBS:
            return "♣"; 
            break;
        case Suits::DIAMONDS:
            return "♢";
            break;
    }
}

// implement constructor for cards
Card::Card(Suits suit, Ranks rank){
    this->suit = suit;
    this->rank = rank;  
    if (suit == Suits::HEARTS || suit == Suits::DIAMONDS) {
        this->color = Colors::RED;
    } else {
        this->color = Colors::BLACK;
    }
}

void Card::printCard() const {
    std::cout << getSuitString(this->suit);
    switch (this->rank) {
        case Ranks::ACE:
            std::cout << 'A';
            break;
        case Ranks::QUEEN:
            std::cout << 'Q';
            break;
        case Ranks::JACK:
            std::cout << 'J';
            break;
        case Ranks::KING:
            std::cout << 'K';
            break;
        default:
            std::cout << static_cast<int>(this->rank);
            break;
    }
}

CardsManager::CardsManager() {
    SetConsoleOutputCP(CP_UTF8);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            available_cards.push_back(Card(static_cast<Suits>(i), static_cast<Ranks>(j)));
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(available_cards.begin(), available_cards.end(), g);
}

Card CardsManager::drawCard() {
    if (available_cards.empty()) {
        throw std::out_of_range("[ERROR] No more cards available to draw.");
    }
    Card card = available_cards.back();
    available_cards.pop_back();
    return card;
}

bool CardsManager::isOrdered(const Card& a, const Card& b) const {
    if(a.getColor() == b.getColor())
        return false;
    if(static_cast<int>(a.getRank()) < static_cast<int>(b.getRank()))
        return true;
    else
        return false;
}

bool CardsManager::haveSameSuits(const Card& a, const Card& b) const {
    return a.getSuit() == b.getSuit();
}

std::vector<Card> CardsManager::getAllCards(){
    std::vector<Card> res = this->available_cards;
    this->available_cards.clear();
    return res;
}