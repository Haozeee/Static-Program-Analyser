#include "catch.hpp"
#include "TestBaseExtractor.h"
#include "source_processor/node/statement_node/ReadNode.h"

TEST_CASE("Test Base Extractor") {
    const std::string procedureName = "procedure";
    const std::string nodeName = "name";
    const int nodeIndex = 1;

    SECTION("Test extractProgram to extractStatement") {
        std::unique_ptr<TestBaseExtractor> baseExtractor = std::make_unique<TestBaseExtractor>();

        // Construct Test AST
        std::vector<std::shared_ptr<StmtNode>> stmtList;
        std::shared_ptr<StmtListNode> stmtListNode = std::make_shared<StmtListNode>(stmtList);
        std::shared_ptr<ProcedureNode> procedureNode =
                std::make_shared<ProcedureNode>(procedureName, stmtListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);

        // Test Empty Program
        REQUIRE_THROWS(baseExtractor->extractProgram(programNode));

        // Test Correct Program Insert
        procedureList.push_back(procedureNode);
        CHECK(procedureNode->procedureName == procedureName);

        // Test Empty Stmt List
        programNode = std::make_shared<ProgramNode>(procedureList);
        REQUIRE_THROWS(baseExtractor->extractProgram(programNode));

        // Test Valid extractStatement
        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(nodeIndex, nodeName);
        stmtList.push_back(readNode);
        stmtListNode = std::make_shared<StmtListNode>(stmtList);
        procedureNode = std::make_shared<ProcedureNode>(procedureName, stmtListNode);
        procedureList.pop_back();
        procedureList.push_back(procedureNode);
        programNode = std::make_shared<ProgramNode>(procedureList);
        REQUIRE_NOTHROW(baseExtractor->extractProgram(programNode));
        CHECK(baseExtractor->getStatementNumber() == nodeIndex);
    }
}
