#pragma once
#include <string>
#include "SuchThatClause.h"
#include "../../Argument.h"
#include "UsesClause.h"

const char USESRELATION[] = "uses";

class SuchThatClauseFactory {
 public:
    /**
     * Factory method to create a new such that clause.
     * @param relation The type of relation.
     * @param leftArg The left argument for the clause.
     * @param rightArg  The right argument for the clause.
     * @return The SuchThatClause object.
     */
    static SuchThatClause* createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg);
};
