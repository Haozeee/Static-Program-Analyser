#pragma once
#include <string>
#include "SuchThatClause.h"
#include "../../Argument.h"
#include "UsesClause.h"

const std::string USESRELATION = "uses";

class SuchThatClauseFactory {
public:
    static SuchThatClause* createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg);
};
