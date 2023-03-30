#include "catch.hpp"
#include <memory>
#include "MockStringStringClauseEvaluator.h"
#include "MockStorageReader.h"

TEST_CASE("Test String String - string, string") {
    // Tests relation with parameter ("a", "b")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "b", DesignEntity::NONE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has Results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has No Results
    leftArg = Argument(ArgumentType::CHARACTERSTRING, "fe", DesignEntity::NONE);
    testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Wildcard Wildcard - string, string") {
    // Tests relation with parameter (_, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    leftArg = Argument(ArgumentType::CHARACTERSTRING, "fe", DesignEntity::NONE);
    testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Synonym Synonym - string, string") {
    // Tests relation with parameter (p, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "p", DesignEntity::PROCEDURE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResultsProc {"a", "b", "d"};
    std::unordered_set<std::string> expectedResultsVar {"b", "c", "d", "e"};
    REQUIRE(res->getColumnValues("p") == expectedResultsProc);
    REQUIRE(res->getColumnValues("v") == expectedResultsVar);
}

TEST_CASE("Test Synonym Wildcard - string, string") {
    // Tests relation with parameter (p, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "p", DesignEntity::PROCEDURE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResultsProc {"a", "b", "d"};
    REQUIRE(res->getColumnValues("p") == expectedResultsProc);
}

TEST_CASE("Test Wildcard Synonym - string, string") {
    // Tests relation with parameter (_, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResultsVar {"b", "c", "d", "e"};
    REQUIRE(res->getColumnValues("v") == expectedResultsVar);
}

TEST_CASE("Test Synonym String - string, string") {
    // Tests relation with parameter (p, "c")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "p", DesignEntity::PROCEDURE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "c", DesignEntity::NONE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResultsProc {"a", "b"};
    REQUIRE(res->getColumnValues("p") == expectedResultsProc);

    // Has no results
    leftArg = Argument(ArgumentType::CHARACTERSTRING, "fe", DesignEntity::NONE);
    testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Wildcard String - string, string") {
    // Tests relation with parameter (_, "c")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::CHARACTERSTRING, "c", DesignEntity::NONE);
    auto testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    rightArg = Argument(ArgumentType::CHARACTERSTRING, "fe", DesignEntity::NONE);
    testEvaluator = MockStringStringClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}
