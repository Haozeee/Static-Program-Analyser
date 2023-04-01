#include "catch.hpp"
#include "query_processing_system/QueryEvaluator.h"
#include "../../../source_processor/design_extractor/MockStore.h"
#include "../clause_evaluator/MockStorageReader.h"
#include "MockIntStringClause.h"
#include <string>
#include <memory>
#include <vector>

TEST_CASE("Select SYNONYM: Select All - int") {
    // Query in the form of stmt s; Select s
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("s");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3", "4", "5"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: Select All - string") {
    // Query in the form of variable v; Select v
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("v");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"a", "b", "c", "d", "e"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int string, (1, v)") {
    // Query in the form of variable v; Select v such that Modifies(1, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("v");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto suchThatClause = MockIntStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"a", "b"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int string, (s, \"a\")") {
    // Query in the form of stmt s; Select s such that Modifies(s, "a")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("s");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    auto suchThatClause = MockIntStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int string, (a, _)") {
    // Query in the form of assign a; Select a such that Modifies(a, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym assign = Synonym("a");
    query->addDeclaration(assign, DesignEntity::ASSIGN);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("a");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::SYNONYM, "a", DesignEntity::ASSIGN);
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockIntStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: int string, TRUE") {
    // Query in the form of variable v; Select BOOLEAN such that Modifies(1, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto suchThatClause = MockIntStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"TRUE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: int string, FALSE") {
    // Query in the form of variable v; Select BOOLEAN such that Modifies(6, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::NUMBER, "6", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto suchThatClause = MockIntStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"FALSE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}
