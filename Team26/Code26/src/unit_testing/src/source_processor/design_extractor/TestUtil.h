#pragma once
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include "source_processor/node/statement_node/IfNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/WhileNode.h"

class TestExtractorUtil {
 public:
    static std::shared_ptr<IfNode> makeSimpleIfNode(int stmtNumber) {
        int ifNo = stmtNumber;
        int thenStmtNumber = ifNo + 1;
        int elseStmtNumber = thenStmtNumber + 1;

        std::unordered_set<std::string> variables { "a" };
        std::unordered_set<int> constants { 1 };

        std::shared_ptr<CondExprNode> condExpr = std::make_shared<CondExprNode>(variables, constants);

        std::shared_ptr<ReadNode> thenReadNode = std::make_shared<ReadNode>(thenStmtNumber, "IfThenRead");
        std::shared_ptr<ReadNode> elseReadNode = std::make_shared<ReadNode>(elseStmtNumber, "IfElseRead");

        std::vector<std::shared_ptr<StmtNode>> thenStmtList;
        thenStmtList.emplace_back(thenReadNode);
        std::shared_ptr<StmtListNode> thenStmtListNode = std::make_shared<StmtListNode>(thenStmtList);

        std::vector<std::shared_ptr<StmtNode>> elseStmtList;
        elseStmtList.emplace_back(elseReadNode);
        std::shared_ptr<StmtListNode> elseStmtListNode = std::make_shared<StmtListNode>(elseStmtList);

        return std::make_shared<IfNode>(ifNo, condExpr, thenStmtListNode, elseStmtListNode);
    }

    static std::shared_ptr<WhileNode> makeSimpleWhileNode(int stmtNumber) {
        int whileNo = stmtNumber;
        int listStmtNo = whileNo + 1;

        std::unordered_set<std::string> variables { "a" };
        std::unordered_set<int> constants { 1 };

        std::shared_ptr<CondExprNode> condExpr = std::make_shared<CondExprNode>(variables, constants);

        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(listStmtNo, "WhileRead");

        std::vector<std::shared_ptr<StmtNode>> whileStmtList;
        whileStmtList.emplace_back(readNode);
        std::shared_ptr<StmtListNode> whileStmtListNode = std::make_shared<StmtListNode>(whileStmtList);

        return std::make_shared<WhileNode>(whileNo, condExpr, whileStmtListNode);
    }

    static std::shared_ptr<WhileNode> makeSimpleNestedWhileNode(int &stmtNumber) {
        /**
         * while (a > 1) {  // stmtNumber
         *   read a;  // stmtNumber + 1
         *   print l; // stmtNumber + 2
         *   while (a > 2) { // stmtNumber + 3
         *     print c; // stmtNumber + 4
         *     read q; // stmtNumber + 5
         *     call callT; // stmtNumber + 6
         *   }
         * }
         *
         * **/
        int start = stmtNumber + 1;
        stmtNumber = stmtNumber + 8;

        // INNER WHILE
        std::unordered_set<std::string> variables2 { "a" };
        std::unordered_set<int> constants2 { 1 };
        std::shared_ptr<CondExprNode> condExpr2 = std::make_shared<CondExprNode>(variables2, constants2);

        std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(start+4, "printC");
        std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(start+5, "readQ");
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(start+6, "callT");

        std::vector<std::shared_ptr<StmtNode>> whileStmtList2;
        whileStmtList2.push_back(printNode2);
        whileStmtList2.push_back(readNode2);
        whileStmtList2.push_back(callNode);
        std::shared_ptr<StmtListNode> whileStmtListNode2 = std::make_shared<StmtListNode>(whileStmtList2);

        std::shared_ptr<WhileNode> innerWhile = std::make_shared<WhileNode>(start+3, condExpr2, whileStmtListNode2);
        // END INNER WHILE

        std::unordered_set<std::string> variables1 { "a" };
        std::unordered_set<int> constants1 { 1 };
        std::shared_ptr<CondExprNode> condExpr1 = std::make_shared<CondExprNode>(variables1, constants1);
        std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(start+1, "readA");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(start+2, "printL");

        std::vector<std::shared_ptr<StmtNode>> whileStmtList1;
        whileStmtList1.push_back(readNode1);
        whileStmtList1.push_back(printNode1);
        whileStmtList1.push_back(innerWhile);
        std::shared_ptr<StmtListNode> whileStmtListNode1 = std::make_shared<StmtListNode>(whileStmtList1);

        return std::make_shared<WhileNode>(start, condExpr1, whileStmtListNode1);
    }
};
