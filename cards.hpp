#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>

enum class Colors {
    BLACK = 0,
    RED = 1,
};

enum class Suits {
    HEARTS = 0,
    DIAMONDS = 1,
    CLUBS = 2,
    SPADES = 3,
};

enum class Ranks {
    ACE = 0,
    TWO = 1,
    THREE = 2,
    FOUR = 3,
    FIVE = 4,
    SIX = 5,
    SEVEN = 6,
    EIGHT = 7,
    NINE = 8,
    TEN = 9,
    JACK = 10,
    QUEEN = 11,
    KING = 12,
};

std::string getSuitString(Suits suit, bool addColor);

class Card {
private:
    Colors color;
    Suits suit;
    Ranks rank;

public:
    Card(Suits suit, Ranks rank);
    Card() : color(static_cast<Colors>(-1)), suit(static_cast<Suits>(-1)), rank(static_cast<Ranks>(-1)) {}

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
    std::vector<std::string> toVec();
};

class CardsManager {
private:
    std::vector<Card> available_cards;
public:
    CardsManager();

    Card drawCard();

    bool isOrdered(const Card &a, const Card &b) const;
    bool haveSameSuits(const Card &a, const Card &b) const;
    std::vector<Card> getAllCards();
};
