#include "catch.hpp"
#include <memory>
#include "MockIntStringClauseEvaluator.h"
#include "MockStorageReader.h"

TEST_CASE("Test Number String") {
    // Tests relation with parameter (1, "a")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has Results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has No Results
    leftArg = Argument(ArgumentType::NUMBER, "4", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Number Wildcard") {
    // Tests relation with parameter (1, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "44", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Wildcard String") {
    // Tests relation with parameter (_, "a")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    rightArg = Argument(ArgumentType::CHARACTERSTRING, "abc", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Wildcard Synonym") {
    // Tests relation with parameter (_, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"a", "b", "c"};
    REQUIRE(res->getColumnValues("v") == expectedResults);
}

TEST_CASE("Test Synonym Wildcard") {
    // Tests relation with parameter (s, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::READ);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"1", "2", "3"};
    REQUIRE(res->getColumnValues("s") == expectedResults);
}

TEST_CASE("Test Value Synonym") {
    // Tests relation with parameter (1, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "v", DesignEntity::STMT);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"a", "b"};
    REQUIRE(res->getColumnValues("v") == expectedResults);

    // No Results
    leftArg = Argument(ArgumentType::NUMBER, "55", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Synonym Value") {
    // Tests relation with parameter (s, "a")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    auto testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"1", "3"};
    REQUIRE(res->getColumnValues("s") == expectedResults);

    // No Results
    rightArg = Argument(ArgumentType::CHARACTERSTRING, "f", DesignEntity::NONE);
    testEvaluator = MockIntStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}
