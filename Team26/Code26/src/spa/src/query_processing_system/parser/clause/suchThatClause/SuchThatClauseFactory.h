#pragma once
#include <string>
#include "SuchThatClause.h"
#include "../../Argument.h"
#include "UsesClause.h"
#include "FollowsClause.h"

const char USESRELATION[] = "Uses";
const char FOLLOWSRELATION[] = "Follows";

class SuchThatClauseFactory {
 public:
    /**
     * Factory method to create a new Such That Clause.
     *
     * @param relation The type of relation.
     * @param leftArg The left argument for the clause.
     * @param rightArg  The right argument for the clause.
     * @return The SuchThatClause object.
     */
    static SuchThatClause* createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg);

    /**
     * Factory method to create a new Follows Clause.
     *
     * @param relation The type of relation.
     * @param leftArg The left argument for the clause.
     * @param rightArg The right argument for the clause.
     * @return The FollowsClause object.
     */
    static FollowsClause* createFollowsClause(std::string relation, Argument leftArg, Argument rightArg);
};