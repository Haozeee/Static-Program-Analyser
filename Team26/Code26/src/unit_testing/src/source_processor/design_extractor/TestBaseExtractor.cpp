#include "catch.hpp"
#include "TestBaseExtractor.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/ExprNode.h"

TEST_CASE("Test Base Extractor") {
    const std::string procedureName = "procedure";
    const std::string nodeName = "name";
    const int nodeIndex = 1;
    const std::string constant = "26";
    const std::string variable = "a";

    SECTION("Test extractProgram to extractStatement") {
        std::unique_ptr<TestBaseExtractor> baseExtractor = std::make_unique<TestBaseExtractor>();

        CHECK(baseExtractor->getExprIntegerList().empty());
        CHECK(baseExtractor->getExprIntegerList().empty());

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

    SECTION("Test extractExpr using Expr") {
        std::unique_ptr<TestBaseExtractor> baseExtractor = std::make_unique<TestBaseExtractor>();

        // AST Setup Single Expr node
        std::shared_ptr<ExprNode> constExprNode = std::make_shared<ExprNode>(constant,
                                                                        ExprNodeType::FACTOR_CONSTANT);
        std::shared_ptr<ExprNode> variableExprNode = std::make_shared<ExprNode>(variable,
                                                                                ExprNodeType::FACTOR_VARIABLE);

        std::shared_ptr<std::tuple<OperatorType, std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>> binaryOPNode = std::make_shared<std::tuple<OperatorType, std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>>(std::make_tuple(OperatorType::ADD,
                                                                                          constExprNode,
                                                                          variableExprNode));
        std::shared_ptr<ExprNode> binaryOPNodeExpr = std::make_shared<ExprNode>(binaryOPNode,"1+a");

        baseExtractor->testExtractExpr(variableExprNode);
        CHECK(baseExtractor->getExprVariableList().size() == 1);
        baseExtractor->testExtractExpr(constExprNode);
        CHECK(baseExtractor->getExprIntegerList().size() == 1);
        baseExtractor->testExtractExpr(binaryOPNodeExpr);
        CHECK(baseExtractor->getExprIntegerList().size() == 2);
        CHECK(baseExtractor->getExprIntegerList().size() == 2);
        baseExtractor->testClearExprStack();
        CHECK(baseExtractor->getExprIntegerList().empty());
        CHECK(baseExtractor->getExprIntegerList().empty());
    }
}