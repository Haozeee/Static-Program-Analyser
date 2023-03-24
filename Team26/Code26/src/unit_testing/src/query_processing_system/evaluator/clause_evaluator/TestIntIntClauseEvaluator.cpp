#include "catch.hpp"
#include "MockIntIntClauseEvaluator.h"
#include <memory>

TEST_CASE("Test Number Number") {
    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::NUMBER, "2", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(nullptr, nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    rightArg = Argument(ArgumentType::NUMBER, "6", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(nullptr, nullptr);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}
