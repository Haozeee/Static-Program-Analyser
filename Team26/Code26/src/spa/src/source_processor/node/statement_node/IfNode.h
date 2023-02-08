#pragma once

#include "StmtNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/StmtListNode.h"

class IfNode : public StmtNode {
 public:
     std::shared_ptr<CondExprNode> condExprNode;
     std::shared_ptr<StmtListNode> thenStmtListNode;
     std::shared_ptr<StmtListNode> elseStmtListNode;

    IfNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode, std::shared_ptr<StmtListNode> thenStmtListNode,
        std::shared_ptr<StmtListNode> elseStmtListNode);

    void evaluate(AbstractExtractor& extractor) override;
};
