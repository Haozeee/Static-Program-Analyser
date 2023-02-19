#include "catch.hpp"
#include "MockIntStringClauseEvaluator.h"
#include <memory>

TEST_CASE("Test Number String") {
    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "v1", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Statement with no children, has results
    testEvaluator.evaluateClause(nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Statement with no children, has no results
    leftArg = Argument(ArgumentType::NUMBER, "4", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Number Wildcard") {
    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Statement with no children, has results
    testEvaluator.evaluateClause(nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Statement with no result
    leftArg = Argument(ArgumentType::NUMBER, "44", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}
