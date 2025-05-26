#include <vector>
#include <variant>
#include "cards.hpp"
#include "move.hpp"

ActionsManager::ActionsManager(PilesManager* pilesManager){
    this->pilesManager = pilesManager;
}

bool ActionsManager::undoMove(){
    if(this->actions.empty())
        return false;

    std::variant<NewReserveAction, MoveAction, DrawAction, AnswerAction> action = this->actions.back();
    std::visit([](auto&& act) {
        using T = std::decay_t<decltype(act)>;
        if constexpr (std::is_same_v<T, NewReserveAction>) {
            // NewReserve Action
            
        }else if constexpr (std::is_same_v<T, MoveAction>) {
            // MoveAction
        }else if constexpr (std::is_same_v<T, DrawAction>) {
            // DrawAction
        }else if constexpr (std::is_same_v<T, AnswerAction>) {
            // AnswerAction
        }
    }, action);

    this->actions.pop_back();
    return true;
}