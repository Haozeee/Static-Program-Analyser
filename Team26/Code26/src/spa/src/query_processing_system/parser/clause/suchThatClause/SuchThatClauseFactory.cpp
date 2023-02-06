#include <utility>

#include "FollowsClause.h"
#include "SuchThatClauseFactory.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"

SuchThatClause *SuchThatClauseFactory::createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg) {
    if (relation == USESRELATION) {
        return new UsesClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == FOLLOWSRELATION) {
        // No such clause, throw error
        throw QueryInvalidRelationship(relation + QueryInvalidRelationshipInSelectClause)
    }
}
