#include "catch.hpp"
#include "query_processing_system/QueryEvaluator.h"
#include "../../../source_processor/design_extractor/MockStore.h"
#include "../mock_storage/MockStorageReader.h"
#include "MockIntStringClause.h"
#include "MockIntIntClause.h"
#include "MockStringStringClause.h"
#include <string>
#include <memory>
#include <vector>

// Tests for Select SYNONYM

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

    // Set up query evaluator
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

    // Set up query evaluator
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

    // Set up query evaluator
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

    // Set up query evaluator
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

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int int, (1, s)") {
    // Query in the form of stmt s; Select s such that Follows(1, s)
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

    Argument left = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int int, (s, a)") {
    // Query in the form of stmt s; assign a; Select s such that Follows(s, a)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    Synonym assign = Synonym("a");
    query->addDeclaration(assign, DesignEntity::ASSIGN);


    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("s");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right = Argument(ArgumentType::SYNONYM, "a", DesignEntity::ASSIGN);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "4"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int int, (s, _)") {
    // Query in the form of stmt s; Select s such that Follows(s, _)
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
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "4"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int int, (_, s)") {
    // Query in the form of stmt s; Select s such that Follows(_, s)
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

    Argument left = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"2", "3", "4", "5"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int int, (_, _)") {
    // Query in the form of stmt s; Select s such that Follows(_, _)
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

    Argument left = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3", "4", "5"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: string string, (\"a\", proc)") {
    // Query in the form of procedure proc; Select proc such that Calls("a", proc)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym proc = Synonym("proc");
    query->addDeclaration(proc, DesignEntity::PROCEDURE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("proc");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::CHARACTERSTRING, "a", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "proc", DesignEntity::PROCEDURE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"b", "c"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: string string, (proc, \"c\")") {
    // Query in the form of procedure proc; Select proc such that Calls(proc, "c")
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym proc = Synonym("proc");
    query->addDeclaration(proc, DesignEntity::PROCEDURE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("proc");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::SYNONYM, "proc", DesignEntity::PROCEDURE);
    Argument right = Argument(ArgumentType::CHARACTERSTRING, "c", DesignEntity::NONE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"a", "b"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: string string, (_, proc)") {
    // Query in the form of procedure proc; Select proc such that Calls(_, proc)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym proc = Synonym("proc");
    query->addDeclaration(proc, DesignEntity::PROCEDURE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("proc");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "proc", DesignEntity::PROCEDURE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"b", "c", "d", "e"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: string string, (proc, _)") {
    // Query in the form of procedure proc; Select proc such that Calls(proc, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym proc = Synonym("proc");
    query->addDeclaration(proc, DesignEntity::PROCEDURE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("proc");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    Argument left = Argument(ArgumentType::SYNONYM, "proc", DesignEntity::PROCEDURE);
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"a", "b", "d"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

// Tests for Select BOOLEAN

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

    // Set up query evaluator
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

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"FALSE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: int int, TRUE") {
    // Query in the form of stmt s; Select BOOLEAN such that Follows(1, s)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::NUMBER, "1", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"TRUE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: int int, FALSE") {
    // Query in the form of stmt s; Select BOOLEAN such that Follows(5, s)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::NUMBER, "5", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    auto suchThatClause = MockIntIntClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"FALSE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: string string, TRUE") {
    // Query in the form of Select BOOLEAN such that Calls(_, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"TRUE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select BOOLEAN: string string, FALSE") {
    // Query in the form of Select BOOLEAN such that Calls("f", _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    auto selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    query->setSelectClause(selectClause);

    Argument left = Argument(ArgumentType::CHARACTERSTRING, "f", DesignEntity::NONE);
    Argument right = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause = MockStringStringClause(left, right);
    query->addSuchThatClause(&suchThatClause);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"FALSE"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

// Tests for multiple clauses

TEST_CASE("Select SYNONYM: int string, (s, _) and (s, _)") {
    // Query in the form of stmt s; Select s such that Modifies(s, _) and Follows(s, _)
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

    // Modifies(s, _)
    Argument left1 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right1 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause1 = MockIntStringClause(left1, right1);
    query->addSuchThatClause(&suchThatClause1);

    // Follows(s, _)
    Argument left2 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right2 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause2 = MockIntStringClause(left2, right2);
    query->addSuchThatClause(&suchThatClause2);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int string, (s, _) and (s, _) and (a, v)") {
    // Query in the form of stmt s; assign a; variable v;
    // Select s such that Modifies(s, _) and Follows(s, _) and Modifies(a, v)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    Synonym assign = Synonym("a");
    query->addDeclaration(assign, DesignEntity::ASSIGN);

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("s");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    // Modifies(s, _)
    Argument left1 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right1 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause1 = MockIntStringClause(left1, right1);
    query->addSuchThatClause(&suchThatClause1);

    // Follows(s, _)
    Argument left2 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right2 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause2 = MockIntStringClause(left2, right2);
    query->addSuchThatClause(&suchThatClause2);

    // Modifies(a, v)
    Argument left3 = Argument(ArgumentType::SYNONYM, "a", DesignEntity::ASSIGN);
    Argument right3 = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto suchThatClause3 = MockIntStringClause(left3, right3);
    query->addSuchThatClause(&suchThatClause3);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}

TEST_CASE("Select SYNONYM: int string, (s, _) and (s, _) and (a, v) and (proc, _)") {
    // Query in the form of stmt s; assign a; variable v;
    // Select s such that Modifies(s, _) and Follows(s, _) and Modifies(a, v) and Calls(proc, _)
    std::shared_ptr<MockStorageReader> testStorage = std::make_shared<MockStorageReader>();

    // Set up query object
    Query *query = new Query();

    Synonym stmt = Synonym("s");
    query->addDeclaration(stmt, DesignEntity::STMT);

    Synonym assign = Synonym("a");
    query->addDeclaration(assign, DesignEntity::ASSIGN);

    Synonym var = Synonym("v");
    query->addDeclaration(var, DesignEntity::VARIABLE);

    Synonym proc = Synonym("proc");
    query->addDeclaration(proc, DesignEntity::PROCEDURE);

    SelectClauseItem selectClauseItem = std::make_shared<Synonym>("s");
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);

    // Modifies(s, _)
    Argument left1 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right1 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause1 = MockIntStringClause(left1, right1);
    query->addSuchThatClause(&suchThatClause1);

    // Follows(s, _)
    Argument left2 = Argument(ArgumentType::SYNONYM, "s", DesignEntity::STMT);
    Argument right2 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause2 = MockIntStringClause(left2, right2);
    query->addSuchThatClause(&suchThatClause2);

    // Modifies(a, v)
    Argument left3 = Argument(ArgumentType::SYNONYM, "a", DesignEntity::ASSIGN);
    Argument right3 = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
    auto suchThatClause3 = MockIntStringClause(left3, right3);
    query->addSuchThatClause(&suchThatClause3);

    // Calls(proc, _)
    Argument left4 = Argument(ArgumentType::SYNONYM, "proc", DesignEntity::PROCEDURE);
    Argument right4 = Argument(ArgumentType::WILDCARD, "_", DesignEntity::NONE);
    auto suchThatClause4 = MockIntStringClause(left4, right4);
    query->addSuchThatClause(&suchThatClause4);

    // Set up query evaluator
    QueryEvaluator QE(query, testStorage);

    // Evaluate query
    auto result = QE.evaluateQuery();
    std::unordered_set<std::string> expectedResult{"1", "2", "3"};
    auto evaluatedResultsVector = result.getInterestedResults();
    std::unordered_set<std::string> evaluatedResults(evaluatedResultsVector.begin(), evaluatedResultsVector.end());
    REQUIRE(evaluatedResults == expectedResult);
}
