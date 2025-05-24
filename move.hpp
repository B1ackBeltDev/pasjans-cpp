#include "cards.hpp";
#include <vector>
#include <variant>

struct MoveAction {
    int fromPile;
    int toPile;
    int howManyCards;
};

struct DrawAction {
    int toPile;
};

struct AnswerAction {
    bool fromReserve;
    int fromPile;
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

    void performLastAction(){
        ;
    }
};