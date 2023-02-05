#include "SuchThatClauseFactory.h"
#include <utility>

SuchThatClause *SuchThatClauseFactory::createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg) {
    if (relation == USESRELATION) {
        return new UsesClause(std::move(leftArg), std::move(rightArg));
    } else {
        // No such clause, throw error
        throw std::exception();
    }
}
