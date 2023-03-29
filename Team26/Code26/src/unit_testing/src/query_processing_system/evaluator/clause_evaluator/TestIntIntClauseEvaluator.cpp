#include "catch.hpp"
#include <memory>
#include "MockIntIntClauseEvaluator.h"
#include "MockStorageReader.h"

TEST_CASE("Test Number Number") {
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::NUMBER, "2", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    rightArg = Argument(ArgumentType::NUMBER, "6", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}
