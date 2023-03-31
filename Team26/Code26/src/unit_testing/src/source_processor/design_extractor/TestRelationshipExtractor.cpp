#include "catch.hpp"
#include "MockStore.h"
#include "TestUtil.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/storage_writer/interface/IStore.h"

TEST_CASE("Test Relationship Extractor") {
    SECTION("1 Procedure") {
        const std::string procedureName = "procedure";
        const std::string readNodeName = "read";
        const std::string printNodeName = "print";
        const std::string assignNodeName = "assign";
        int nodeIndex = 1;  // NOTE OLD TESTCASES STARTS AT 1
        const std::string constant = "26";
        const std::string variable = "a";

        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();

        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);
        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(nodeIndex++, readNodeName);
        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(nodeIndex++, printNodeName);
        auto ifNode = TestExtractorUtil::makeSimpleIfNode(nodeIndex);
        nodeIndex = nodeIndex + 3;
        auto whileNode = TestExtractorUtil::makeSimpleWhileNode(nodeIndex);
        nodeIndex = nodeIndex + 2;
        std::unordered_set<std::string> variables { variable };
        std::unordered_set<int> constants { stoi(constant) };

        std::unordered_set<std::string> emptyVariables;
        std::unordered_set<int> emptyConstants;

        std::shared_ptr<ShuntNode> constShuntNode = std::make_shared<ShuntNode>(constant);
        std::shared_ptr<ShuntNode> variableShuntNode = std::make_shared<ShuntNode>(variable);


        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName,
                                                                               constShuntNode, emptyVariables,
                                                                               constants);

        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(nodeIndex++, assignNodeName + "1",
                                                                               variableShuntNode, variables, emptyConstants);

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

        relationshipExtractor->extractProgram(programNode);

        /*
         * 1. read
         * 2. print
         * 3. if
         * 4. if -> read
         * 5. else -> read
         * 6. while
         * 7. while -> read
         * 8. assign
         * 9. assign
         * */
        REQUIRE(relationshipStore->findFollows(1,2));
        REQUIRE(relationshipStore->findFollows(2,3));
        REQUIRE(relationshipStore->findFollows(3,6));
        REQUIRE(relationshipStore->findFollows(6,8));
        REQUIRE(relationshipStore->findFollows(8,9));

        REQUIRE(relationshipStore->findParents(6,7));
        REQUIRE(relationshipStore->findParents(3,4));
        REQUIRE(relationshipStore->findParents(3,5));

        REQUIRE(relationshipStore->findUseS(2,"print"));
        REQUIRE(relationshipStore->findUseS(9,"a"));

        REQUIRE(relationshipStore->findModifiesS(1,"read"));
        REQUIRE(relationshipStore->findModifiesS(3,"IfThenRead"));
        REQUIRE(relationshipStore->findModifiesS(3,"IfElseRead"));
        REQUIRE(relationshipStore->findModifiesS(4,"IfThenRead"));
        REQUIRE(relationshipStore->findModifiesS(5,"IfElseRead"));
        REQUIRE(relationshipStore->findModifiesS(6,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(7,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(8,"assign"));
        REQUIRE(relationshipStore->findModifiesS(9,"assign1"));
    }

    SECTION("2 Procedure with Call") {

        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();

        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);

        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";
        const std::string printNodeName = "print";
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(nodeIndex++, callNodeName);
        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(nodeIndex++, printNodeName);

        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        std::vector<std::shared_ptr<StmtNode>> stmtList2;
        stmtList2.emplace_back(printNode);
        std::shared_ptr<StmtListNode> stmtListNode2 = std::make_shared<StmtListNode>(stmtList2);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(firstProcedureName, stmtListNode1);
        std::shared_ptr<ProcedureNode> procedureNode2 =
                std::make_shared<ProcedureNode>(callNodeName, stmtListNode2);

        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        procedureList.emplace_back(procedureNode2);

        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(callNodeName);
        relationshipStore->procedureStore.insert(firstProcedureName);
        relationshipExtractor->extractProgram(programNode);
    }

    SECTION("3 Procedure with Call") {
        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();

        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);

        /**
        * procedure a { call callNode1; } // line 1
        * procedure callNode1 { callNode2 }; // line 2
         * procedure callNode2 { print print }; // line 3
        * **/

        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";
        const std::string callNodeName2 = "callNode2";
        const std::string printNodeName = "print";
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(nodeIndex++, callNodeName);
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(nodeIndex++, callNodeName2);
        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(nodeIndex++, printNodeName);

        // first proc
        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        // second proc
        std::vector<std::shared_ptr<StmtNode>> stmtList2;
        stmtList2.emplace_back(callNode2);
        std::shared_ptr<StmtListNode> stmtListNode2 = std::make_shared<StmtListNode>(stmtList2);

        // third proc
        std::vector<std::shared_ptr<StmtNode>> stmtList3;
        stmtList3.emplace_back(printNode);
        std::shared_ptr<StmtListNode> stmtListNode3 = std::make_shared<StmtListNode>(stmtList3);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(firstProcedureName, stmtListNode1);

        std::shared_ptr<ProcedureNode> procedureNode2 =
                std::make_shared<ProcedureNode>(callNodeName, stmtListNode2);

        std::shared_ptr<ProcedureNode> procedureNode3 =
                std::make_shared<ProcedureNode>(callNodeName2, stmtListNode3);

        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        procedureList.emplace_back(procedureNode2);
        procedureList.emplace_back(procedureNode3);

        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(callNodeName);
        relationshipStore->procedureStore.insert(firstProcedureName);
        relationshipStore->procedureStore.insert(callNodeName2);

        relationshipExtractor->extractProgram(programNode);
    }

    SECTION("2 Procedure with Call including If and While") {
        /**
         * procedure a { call callNode1; }
         * procedure callNode1 { if (...)
         * then { read IfThenRead; }
         * else { read IfElseRead; } }
         * while (...) {
         * read WhileRead; }
         * **/

        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();

        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);
        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";

        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(++nodeIndex, callNodeName);

        auto ifNode = TestExtractorUtil::makeSimpleIfNode(nodeIndex);
        nodeIndex = nodeIndex + 3;
        auto whileNode = TestExtractorUtil::makeSimpleWhileNode(nodeIndex);

        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        std::vector<std::shared_ptr<StmtNode>> stmtList2;
        stmtList2.emplace_back(ifNode);
        stmtList2.emplace_back(whileNode);
        std::shared_ptr<StmtListNode> stmtListNode2 = std::make_shared<StmtListNode>(stmtList2);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(firstProcedureName, stmtListNode1);
        std::shared_ptr<ProcedureNode> procedureNode2 =
                std::make_shared<ProcedureNode>(callNodeName, stmtListNode2);

        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        procedureList.emplace_back(procedureNode2);

        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(callNodeName);
        relationshipStore->procedureStore.insert(firstProcedureName);
        relationshipExtractor->extractProgram(programNode);
    }

    SECTION("2 Procedure with Call including Assign") {
        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();

        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);

        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";
        const std::string assignNodeName = "assign";

        // AssignNode
        const std::string constant = "26";
        const std::string variable = "a";
        std::unordered_set<std::string> variables { variable };
        std::unordered_set<int> constants { stoi(constant) };

        std::unordered_set<std::string> emptyVariables;
        std::unordered_set<int> emptyConstants;

        std::shared_ptr<ShuntNode> constShuntNode = std::make_shared<ShuntNode>(constant);
        std::shared_ptr<ShuntNode> variableShuntNode = std::make_shared<ShuntNode>(variable);
        // End

        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(++nodeIndex, callNodeName);
        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(++nodeIndex, assignNodeName,
                                                                               variableShuntNode, variables, emptyConstants);
        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        std::vector<std::shared_ptr<StmtNode>> stmtList2;
        stmtList2.emplace_back(assignNode);
        std::shared_ptr<StmtListNode> stmtListNode2 = std::make_shared<StmtListNode>(stmtList2);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(firstProcedureName, stmtListNode1);
        std::shared_ptr<ProcedureNode> procedureNode2 =
                std::make_shared<ProcedureNode>(callNodeName, stmtListNode2);

        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        procedureList.emplace_back(procedureNode2);

        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(callNodeName);
        relationshipStore->procedureStore.insert(firstProcedureName);
        relationshipExtractor->extractProgram(programNode);
    }

    SECTION("2 Procedure with Nested While Call") {
        /**
         * procedure a { call callNode1; } // 1
         * procedure callNode1 { while (a > 1) { // 2
         *   read a; // 3
         *   print l; // 4
         *   while (a > 2) { // 5
         *     print c; // 6
         *     read q; // 7
         *     call callT; // 8 } } }
         * procedure callT { while (a > 1) // 9 {
         * read WhileRead; // 10 } }
         * **/

        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();
        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>(relationshipStore);

        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";
        const std::string callNodeName3 = "callT";

        // First Procedure
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(++nodeIndex, callNodeName);
        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>(firstProcedureName,stmtListNode1);

        // Second Procedure
        std::shared_ptr<WhileNode> whileNode = TestExtractorUtil::makeSimpleNestedWhileNode(nodeIndex);
        std::vector<std::shared_ptr<StmtNode>> stmtList2;
        stmtList2.emplace_back(whileNode);
        std::shared_ptr<StmtListNode> stmtListNode2 = std::make_shared<StmtListNode>(stmtList2);
        std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>(callNodeName,stmtListNode2);

        // Third Procedure
        auto whileNode3 = TestExtractorUtil::makeSimpleWhileNode(nodeIndex);
        nodeIndex = nodeIndex + 2;
        std::vector<std::shared_ptr<StmtNode>> stmtList3;
        stmtList3.emplace_back(whileNode3);
        std::shared_ptr<StmtListNode> stmtListNode3 = std::make_shared<StmtListNode>(stmtList3);
        std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>(callNodeName3,
                                                                                        stmtListNode3);
        // Program
        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        procedureList.emplace_back(procedureNode2);
        procedureList.emplace_back(procedureNode3);
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);

        // EntityStore Setup
        relationshipStore->procedureStore.insert(callNodeName);
        relationshipStore->procedureStore.insert(firstProcedureName);
        relationshipStore->procedureStore.insert(callNodeName3);

        // Extraction
        relationshipExtractor->extractProgram(programNode);

        REQUIRE(relationshipStore->findFollows(3,4));
        REQUIRE(relationshipStore->findFollows(4,5));
        REQUIRE(relationshipStore->findFollows(6,7));
        REQUIRE(relationshipStore->findFollows(7,8));

        REQUIRE(relationshipStore->findFollowsT(3,4));
        REQUIRE(relationshipStore->findFollowsT(3,5));
        REQUIRE(relationshipStore->findFollowsT(4,5));
        REQUIRE(relationshipStore->findFollowsT(6,7));
        REQUIRE(relationshipStore->findFollowsT(6,8));
        REQUIRE(relationshipStore->findFollowsT(7,8));

        REQUIRE(relationshipStore->findParents(5,6));
        REQUIRE(relationshipStore->findParents(5,7));
        REQUIRE(relationshipStore->findParents(5,8));

        REQUIRE(relationshipStore->findParents(2,3));
        REQUIRE(relationshipStore->findParents(2,4));
        REQUIRE(relationshipStore->findParents(2,5));
        REQUIRE(relationshipStore->findParents(9,10));

        REQUIRE(relationshipStore->findParentsT(2,3));
        REQUIRE(relationshipStore->findParentsT(2,4));
        REQUIRE(relationshipStore->findParentsT(2,5));
        REQUIRE(relationshipStore->findParentsT(2,6));
        REQUIRE(relationshipStore->findParentsT(2,7));
        REQUIRE(relationshipStore->findParentsT(2,8));

        REQUIRE(relationshipStore->findParentsT(5,6));
        REQUIRE(relationshipStore->findParentsT(5,7));
        REQUIRE(relationshipStore->findParentsT(5,8));

        REQUIRE(relationshipStore->findParentsT(9,10));

        REQUIRE(relationshipStore->findUseS(1,"printC"));
        REQUIRE(relationshipStore->findUseS(2,"printC"));
        REQUIRE(relationshipStore->findUseS(5,"printC"));
        REQUIRE(relationshipStore->findUseS(6,"printC"));
        REQUIRE(relationshipStore->findUseS(1,"printL"));
        REQUIRE(relationshipStore->findUseS(2,"printL"));
        REQUIRE(relationshipStore->findUseS(4,"printL"));
        REQUIRE(relationshipStore->findUseS(1,"a"));
        REQUIRE(relationshipStore->findUseS(2,"a"));
        REQUIRE(relationshipStore->findUseS(5,"a"));
        REQUIRE(relationshipStore->findUseS(8,"a"));

        REQUIRE(relationshipStore->findUseP("callNode1","printC"));
        REQUIRE(relationshipStore->findUseP("a","printC"));
        REQUIRE(relationshipStore->findUseP("a","printL"));
        REQUIRE(relationshipStore->findUseP("callNode1","printL"));
        REQUIRE(relationshipStore->findUseP("callT","a"));
        REQUIRE(relationshipStore->findUseP("callNode1","a"));
        REQUIRE(relationshipStore->findUseP("a","a"));

        REQUIRE(relationshipStore->findModifiesS(1,"readA"));
        REQUIRE(relationshipStore->findModifiesS(2,"readA"));
        REQUIRE(relationshipStore->findModifiesS(3,"readA"));
        REQUIRE(relationshipStore->findModifiesS(1,"readQ"));
        REQUIRE(relationshipStore->findModifiesS(2,"readQ"));
        REQUIRE(relationshipStore->findModifiesS(5,"readQ"));
        REQUIRE(relationshipStore->findModifiesS(7,"readQ"));
        REQUIRE(relationshipStore->findModifiesS(1,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(2,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(5,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(8,"WhileRead"));
        REQUIRE(relationshipStore->findModifiesS(9,"WhileRead"));

        REQUIRE(relationshipStore->findModifiesP("a","WhileRead"));
        REQUIRE(relationshipStore->findModifiesP("a","readQ"));
        REQUIRE(relationshipStore->findModifiesP("a","readA"));
        REQUIRE(relationshipStore->findModifiesP("callT","WhileRead"));
        REQUIRE(relationshipStore->findModifiesP("callNode1","WhileRead"));
        REQUIRE(relationshipStore->findModifiesP("callNode1","readQ"));
        REQUIRE(relationshipStore->findModifiesP("callNode1","readA"));

        REQUIRE(relationshipStore->findNext(2,3));
        REQUIRE(relationshipStore->findNext(3,4));
        REQUIRE(relationshipStore->findNext(5,2));
        REQUIRE(relationshipStore->findNext(5,6));
        REQUIRE(relationshipStore->findNext(6,7));
        REQUIRE(relationshipStore->findNext(7,8));
        REQUIRE(relationshipStore->findNext(8,5));
        REQUIRE(relationshipStore->findNext(9,10));
        REQUIRE(relationshipStore->findNext(10,9));

        REQUIRE(relationshipStore->findCallsS(1,"callNode1"));
        REQUIRE(relationshipStore->findCallsP("a","callNode1"));

        REQUIRE(relationshipStore->findCallsS(8,"callT"));
        REQUIRE(relationshipStore->findCallsP("callNode1","callT"));

        REQUIRE(relationshipStore->findCallsT("a","callT"));
        REQUIRE(relationshipStore->findCallsT("a","callNode1"));
        REQUIRE(relationshipStore->findCallsT("callNode1","callT"));
    }

    SECTION("Call Non Existent") {
        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();
        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);

        int nodeIndex = 0;
        const std::string  firstProcedureName = "a";
        const std::string callNodeName = "callNode1";
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(++nodeIndex, callNodeName);

        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(firstProcedureName, stmtListNode1);
        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(firstProcedureName);
        REQUIRE_THROWS(relationshipExtractor->extractProgram(programNode));
    }

    SECTION("Self-Call") {
        std::shared_ptr<MockRelationshipStore> relationshipStore = std::make_shared<MockRelationshipStore>();
        std::unique_ptr<RelationshipExtractor> relationshipExtractor = std::make_unique<RelationshipExtractor>
                (relationshipStore);

        int nodeIndex = 0;
        const std::string callNodeName = "callNode1";
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(++nodeIndex, callNodeName);

        std::vector<std::shared_ptr<StmtNode>> stmtList1;
        stmtList1.emplace_back(callNode);
        std::shared_ptr<StmtListNode> stmtListNode1 = std::make_shared<StmtListNode>(stmtList1);

        std::shared_ptr<ProcedureNode> procedureNode1 =
                std::make_shared<ProcedureNode>(callNodeName, stmtListNode1);
        std::vector<std::shared_ptr<ProcedureNode>> procedureList;
        procedureList.emplace_back(procedureNode1);
        std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>(procedureList);
        relationshipStore->procedureStore.insert(callNodeName);
        REQUIRE_THROWS(relationshipExtractor->extractProgram(programNode));
    }
}
