#include <utility>
#include <iostream>

#include "SuchThatClauseFactory.h"


bool SuchThatClauseFactory::isModifiesOrUsesRelation(std::string relation) {
    return (relation == ModifiesRelation || relation == UsesRelation);
}

SuchThatClause* SuchThatClauseFactory::createModifiesOrUsesClause(std::string relation, Argument leftArg, Argument rightArg) {
    ArgumentType leftArgType = leftArg.getArgumentType();
    if (leftArgType == ArgumentType::SYNONYM) { // checks if first argument type is a Synonym
        Query query;
        DesignEntity leftArgDesignEntity = leftArg.getDesignEntity();
        if (leftArgDesignEntity == DesignEntity::PROCEDURE) { // check if Synonym is a procedure
            if (relation == ModifiesRelation) {
                return new ModifiesPClause(leftArg, rightArg);
            } else {
                return new UsesPClause(leftArg, rightArg);
            }
        } else { // else the Synonym is a statement
            if (relation == ModifiesRelation) {
                return new ModifiesSClause(leftArg, rightArg);
            } else {
                return new UsesSClause(leftArg, rightArg);
            }
        }
    } else { // unknown Argument Type
        throw QueryInvalidRelationship(relation + QueryParserInvalidRelationshipInSelectClause);
    }
}

SuchThatClause *SuchThatClauseFactory::createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg) {
    if (isModifiesOrUsesRelation(relation)) {
        return createModifiesOrUsesClause(relation, leftArg, rightArg);
    }

    if (relation == FollowsRelation) {
        return new FollowsClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == FollowsTRelation) {
        return new FollowsTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentRelation) {
        return new ParentClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentTRelation) {
        return new ParentTClause(std::move(leftArg), std::move(rightArg));
    } else {
        // No such relation, throw error
        throw QueryInvalidRelationship(relation + QueryParserInvalidRelationshipInSelectClause);
    }
}
