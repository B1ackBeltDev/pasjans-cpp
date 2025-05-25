#pragma once
#include <vector>
#include <variant>
#include "cards.hpp"

struct NewReserveAction{
    std::vector<Card> revealdCards;
    std::vector<Card> hiddenCards;
};

struct MoveAction {
    // bool fromReserve;
    int fromPile;
    int toPile;
    int howManyCards;
    bool revealdNew;
    std::vector<Card> cards;
};

struct DrawAction {
    int toPile;
    Card card;
};

struct AnswerAction {
    bool fromReserve;
    int fromPile;
    bool revealdNew;
    Card card;
};

class ActionsManager {
private:
    std::vector<std::variant<MoveAction, DrawAction, AnswerAction>> actions;

public: 
    void addAction(const MoveAction& action) {
        actions.push_back(action);
    }

    void addAction(const DrawAction& action) {
        actions.push_back(action);
    }

    void addAction(const AnswerAction& action) {
        actions.push_back(action);
    }

};