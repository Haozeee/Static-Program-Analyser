#include <utility>
#include <iostream>

#include "SuchThatClauseFactory.h"

SuchThatClause *SuchThatClauseFactory::createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg) {
    if (relation == ModifiesRelation || relation == UsesRelation) {
        ArgumentType leftArgType = leftArg.getArgumentType();
        if (leftArgType == ArgumentType::WILDCARD) {
            // Wildcards cannot be created
            throw QueryValidationException(relation + QueryValidatorInvalidModifiesOrUsesRelationshipInSelectClause);
        }
        DesignEntity leftArgDesignEntity = leftArg.getDesignEntity();
        if ((leftArgType == ArgumentType::SYNONYM && leftArgDesignEntity == DesignEntity::PROCEDURE)
            || leftArgType == ArgumentType::CHARACTERSTRING) {
            if (relation == ModifiesRelation) {
//                std::cout << "modifies procedure" << std::endl;
                return new ModifiesPClause(leftArg, rightArg);
            } else {
//                std::cout << "uses procedure" << std::endl;
                return new UsesPClause(leftArg, rightArg);
            }
        } else {
            if (relation == ModifiesRelation) {
//                std::cout << "modifies statement" << std::endl;
                return new ModifiesSClause(leftArg, rightArg);
            } else {
//                std::cout << "uses procedure" << std::endl;
                return new UsesSClause(leftArg, rightArg);
            }
        }
    } else if (relation == AffectsRelation) {
        return new AffectsClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == AffectsTRelation) {
        return new AffectsTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == CallsRelation) {
        return new CallsClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == CallsTRelation) {
        return new CallsTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == FollowsRelation) {
        return new FollowsClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == FollowsTRelation) {
        return new FollowsTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == NextRelation) {
        return new NextClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == NextTRelation) {
        return new NextTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentRelation) {
        return new ParentClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentTRelation) {
        return new ParentTClause(std::move(leftArg), std::move(rightArg));
    } else {
        // No such relation, throw error
        throw QueryInvalidRelationship(relation + QueryParserInvalidRelationshipInSelectClause);
    }
}
