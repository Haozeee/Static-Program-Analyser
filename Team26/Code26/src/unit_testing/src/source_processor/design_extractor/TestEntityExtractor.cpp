#include <set>
#include "catch.hpp"
#include "MockStore.h"
#include "TestUtil.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/storage/interface/IStore.h"

TEST_CASE("Test Entity Extractor") {
    SECTION("Single Procedure") {

        const std::string procedureName = "procedure";
        const std::string readNodeName = "read";
        const std::string printNodeName = "print";
        const std::string assignNodeName = "assign";
        int nodeIndex = 1;
        const std::string constant = "26";
        const std::string variable = "a";

        std::shared_ptr<MockEntityStore> entityStore = std::make_shared<MockEntityStore>();

        std::unique_ptr<EntityExtractor> entityExtractor = std::make_unique<EntityExtractor>(entityStore);
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


        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName, constExprNode);
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

        entityExtractor->extractProgram(programNode);


        REQUIRE(entityStore->procedureSet.size() == 1);
        REQUIRE(entityStore->stmtSet.size() == 9);
        REQUIRE(entityStore->readSet.size() == 4);
        REQUIRE(entityStore->printSet.size() == 1);
        REQUIRE(entityStore->assignSet.size() == 2);
        REQUIRE(entityStore->whileSet.size() == 1);
        REQUIRE(entityStore->ifSet.size() == 1);
        REQUIRE(entityStore->variableSet.size() == 1);
        REQUIRE(entityStore->constantSet.size() == 2);

        REQUIRE(entityStore->procedureSet.begin()->get()->procedureName == procedureNode->procedureName);
    }
}