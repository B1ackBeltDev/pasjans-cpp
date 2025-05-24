#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>

enum class Colors {
    BLACK,
    RED,
};

enum class Suits {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
};

enum class Ranks {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

std::string getSuitString(Suits suit);

class Card {
private:
    Colors color;
    Suits suit;
    Ranks rank;

public:
    Card(Suits suit, Ranks rank);

    Colors getColor() const {
        return color;
    }

    Suits getSuit() const {
        return suit;
    }

    Ranks getRank() const {
        return rank;
    }

    void printCard() const;
};

class CardsManager {
private:
    std::vector<Card> available_cards;
public:
    CardsManager();

    Card drawCard();

    bool isOrdered(const Card& a, const Card& b) const;
    bool haveSameSuits(const Card& a, const Card&b) const;
    std::vector<Card> getAllCards();
};
