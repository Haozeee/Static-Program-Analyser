#include "catch.hpp"
#include "MockStore.h"
#include "TestUtil.h"
#include "source_processor/design_extractor/extractor/PatternExtractor.h"
#include "source_processor/storage_writer/interface/IStore.h"

TEST_CASE("Test Pattern Extractor") {

    SECTION("Single Procedure") {
        const std::string procedureName = "procedure";
        const std::string readNodeName = "read";
        const std::string printNodeName = "print";
        const std::string assignNodeName = "assign";
        int nodeIndex = 1;
        const std::string constant = "26";
        const std::string variable = "a";

        std::shared_ptr<MockPatternStore> mockPatternStore = std::make_shared<MockPatternStore>();

        std::unique_ptr<PatternExtractor> patternExtractor = std::make_unique<PatternExtractor>(
                mockPatternStore);
        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(nodeIndex++, readNodeName);
        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(nodeIndex++, printNodeName);
        auto ifNode = TestExtractorUtil::makeSimpleIfNode(nodeIndex);
        nodeIndex = nodeIndex + 3;
        auto whileNode = TestExtractorUtil::makeSimpleWhileNode(nodeIndex);
        nodeIndex = nodeIndex + 2;
        std::shared_ptr<ExprNode> constExprNode = std::make_shared<ExprNode>(constant,
                                                                             ExprNodeType::FACTOR_CONSTANT);
        std::shared_ptr<ExprNode> variableExprNode = std::make_shared<ExprNode>(variable,
                                                                                ExprNodeType::FACTOR_VARIABLE);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName,
                                                                               constExprNode);
        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName + "1",
                                                                               variableExprNode);
        std::vector<std::shared_ptr<StmtNode>> stmtList;
        stmtList.emplace_back(readNode);
        stmtList.emplace_back(printNode);
        stmtList.emplace_back(ifNode);
        stmtList.emplace_back(whileNode);
        stmtList.emplace_back(assignNode1);
        stmtList.emplace_back(assignNode2);

        std::shared_ptr<StmtListNode> stmtListNode = std::make_shared<StmtListNode>(stmtList);
        std::shared_ptr<ProcedureNode> procedureNode =
                std::make_shared<ProcedureNode>(procedureName, stmtListNode);
        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode);
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);

        patternExtractor->extractProgram(programNode);

        REQUIRE(mockPatternStore->assignStore.size() == 2);
    }
}