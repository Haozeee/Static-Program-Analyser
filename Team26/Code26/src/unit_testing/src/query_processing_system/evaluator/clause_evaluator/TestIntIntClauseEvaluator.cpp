#include "catch.hpp"
#include <memory>
#include "MockIntIntClauseEvaluator.h"
#include "../mock_storage/MockStorageReader.h"

TEST_CASE("Test Number Number - int, int") {
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

TEST_CASE("Test Synonym Synonym - int, int") {
    // Tests relation with parameter (s, cl)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "cl", DesignEntity::CALL);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResultsStmt {"1", "2", "4"};
    std::unordered_set<std::string> expectedResultsCall {"2", "3", "4", "5"};
    REQUIRE(res->getColumnValues("s") == expectedResultsStmt);
    REQUIRE(res->getColumnValues("cl") == expectedResultsCall);
}

TEST_CASE("Test Wildcard Wildcard - int, int") {
    // Tests relation with parameter (_, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "7", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Synonym Number - int, int") {
    // Tests relation with parameter (s, 2)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument rightArg = Argument(ArgumentType::NUMBER, "2", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"1"};
    REQUIRE(res->getColumnValues("s") == expectedResults);

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "7", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Number Synonym - int, int") {
    // Tests relation with parameter (1, s)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"2", "3"};
    REQUIRE(res->getColumnValues("s") == expectedResults);

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "7", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Synonym Wildcard - int, int") {
    // Tests relation with parameter (s, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"1", "2", "4"};
    REQUIRE(res->getColumnValues("s") == expectedResults);
}

TEST_CASE("Test Wildcard Synonym - int, int") {
    // Tests relation with parameter (_, pn)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "pn", DesignEntity::PRINT);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    std::unordered_set<std::string> expectedResults {"2", "3", "4", "5"};
    REQUIRE(res->getColumnValues("pn") == expectedResults);
}

TEST_CASE("Test Number Wildcard - int, int") {
    // Tests relation with parameter (1, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "7", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Wildcard Number - int, int") {
    // Tests relation with parameter (_, 2)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument rightArg = Argument(ArgumentType::NUMBER, "2", DesignEntity::NONE);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has results
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE_FALSE(res->hasNoResults());

    // Has no results
    leftArg = Argument(ArgumentType::NUMBER, "7", DesignEntity::NONE);
    testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);
    testEvaluator.evaluateClause(testStorage);
    res = testEvaluator.getClauseResult();
    REQUIRE(res->hasNoResults());
}

TEST_CASE("Test Equal Synonym - int, int") {
    // Tests relation with parameter (s, s)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up
    Argument leftArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument rightArg = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto testEvaluator = MockIntIntClauseEvaluator(leftArg, rightArg);

    // Evaluation Results
    std::shared_ptr<ResultTable> res;

    // Has no results
    res = testEvaluator.evaluateClause(testStorage);
    REQUIRE(res->hasNoResults());
    std::unordered_set<std::string> expectedResults {};
    REQUIRE(res->getColumnValues("s") == expectedResults);
}
