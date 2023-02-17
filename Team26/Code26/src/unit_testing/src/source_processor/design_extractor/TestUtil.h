#pragma once
#include <vector>
#include "source_processor/node/statement_node/IfNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/ExprNode.h"
#include "source_processor/node/statement_node/WhileNode.h"

class TestExtractorUtil {
 public:
    static std::shared_ptr<IfNode> makeSimpleIfNode(int stmtNumber) {
        int ifNo = stmtNumber;
        int thenStmtNumber = ifNo + 1;
        int elseStmtNumber = thenStmtNumber + 1;

        auto constExprNode1 = std::make_shared<ExprNode>("1", ExprNodeType::FACTOR_CONSTANT);
        auto constExprNode2 = std::make_shared<ExprNode>("1", ExprNodeType::FACTOR_CONSTANT);

        std::shared_ptr<RelExpr> relExpr = std::make_shared<RelExpr>(
                std::make_tuple(RelExprOperatorType::EQ, constExprNode1, constExprNode2)
                );
        std::shared_ptr<CondExprNode> condExpr = std::make_shared<CondExprNode>(relExpr, "1=1");

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

        auto constExprNode1 = std::make_shared<ExprNode>("1", ExprNodeType::FACTOR_CONSTANT);
        auto constExprNode2 = std::make_shared<ExprNode>("1", ExprNodeType::FACTOR_CONSTANT);

        std::shared_ptr<RelExpr> relExpr = std::make_shared<RelExpr>(
                std::make_tuple(RelExprOperatorType::EQ, constExprNode1, constExprNode2)
        );
        std::shared_ptr<CondExprNode> condExpr = std::make_shared<CondExprNode>(relExpr, "1=1");

        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(listStmtNo, "WhileRead");

        std::vector<std::shared_ptr<StmtNode>> whileStmtList;
        whileStmtList.emplace_back(readNode);
        std::shared_ptr<StmtListNode> whileStmtListNode = std::make_shared<StmtListNode>(whileStmtList);

        return std::make_shared<WhileNode>(whileNo, condExpr, whileStmtListNode);
    }
};