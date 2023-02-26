#include "catch.hpp"
#include "MockStore.h"
#include "TestUtil.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/storage/interface/IStore.h"

TEST_CASE("Test Relationship Extractor") {

//    SECTION("Single Procedure") {
//        const std::string procedureName = "procedure";
//        const std::string readNodeName = "read";
//        const std::string printNodeName = "print";
//        const std::string assignNodeName = "assign";
//        int nodeIndex = 1;
//        const std::string constant = "26";
//        const std::string variable = "a";
//
//        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();
//
//        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
//                (relationshipStore, nullptr);
//        // TODO(ZT: Update Mocking
//        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(nodeIndex++, readNodeName);
//        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(nodeIndex++, printNodeName);
//        auto ifNode = TestExtractorUtil::makeSimpleIfNode(nodeIndex);
//        nodeIndex = nodeIndex + 3;
//        auto whileNode = TestExtractorUtil::makeSimpleWhileNode(nodeIndex);
//        nodeIndex = nodeIndex + 2;
//        std::shared_ptr<ExprNode> constExprNode = std::make_shared<ExprNode>(constant,
//                                                                             ExprNodeType::FACTOR_CONSTANT);
//        std::shared_ptr<ExprNode> variableExprNode = std::make_shared<ExprNode>(variable,
//                                                                                ExprNodeType::FACTOR_VARIABLE);
//        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName, constExprNode);
//        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName + "1",
//                                                                               variableExprNode);
//        std::vector<std::shared_ptr<StmtNode>> stmtList;
//        stmtList.emplace_back(readNode);
//        stmtList.emplace_back(printNode);
//        stmtList.emplace_back(ifNode);
//        stmtList.emplace_back(whileNode);
//        stmtList.emplace_back(assignNode1);
//        stmtList.emplace_back(assignNode2);
//
//        std::shared_ptr<StmtListNode> stmtListNode = std::make_shared<StmtListNode>(stmtList);
//        std::shared_ptr<ProcedureNode> procedureNode =
//                std::make_shared<ProcedureNode>(procedureName, stmtListNode);
//        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
//        procedureList.emplace_back(procedureNode);
//        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
//
//        relationshipExtractor->extractProgram(programNode);
//
//        /*
//         * 1. read
//         * 2. print
//         * 3. if
//         * 4. if -> read
//         * 5. else -> read
//         * 6. while
//         * 7. while -> read
//         * 8. assign
//         * 9. assign
//         * */
//        REQUIRE(relationshipStore->findFollows(1,2));
//        REQUIRE(relationshipStore->findFollows(2,3));
//        REQUIRE(relationshipStore->findFollows(3,6));
//        REQUIRE(relationshipStore->findFollows(6,8));
//        REQUIRE(relationshipStore->findFollows(8,9));
//
//        REQUIRE(relationshipStore->findParents(6,7));
//        REQUIRE(relationshipStore->findParents(3,4));
//        REQUIRE(relationshipStore->findParents(3,5));
//
//        REQUIRE(relationshipStore->findUseS(2,"print"));
//        REQUIRE(relationshipStore->findUseS(9,"a"));
//
//        REQUIRE(relationshipStore->findModifiesS(1,"read"));
//        REQUIRE(relationshipStore->findModifiesS(3,"IfThenRead"));
//        REQUIRE(relationshipStore->findModifiesS(3,"IfElseRead"));
//        REQUIRE(relationshipStore->findModifiesS(4,"IfThenRead"));
//        REQUIRE(relationshipStore->findModifiesS(5,"IfElseRead"));
//        REQUIRE(relationshipStore->findModifiesS(6,"WhileRead"));
//        REQUIRE(relationshipStore->findModifiesS(7,"WhileRead"));
//        REQUIRE(relationshipStore->findModifiesS(8,"assign"));
//        REQUIRE(relationshipStore->findModifiesS(9,"assign1"));
//    }

}