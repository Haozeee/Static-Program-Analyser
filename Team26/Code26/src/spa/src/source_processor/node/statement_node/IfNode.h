#pragma once

#include <memory>
#include "source_processor/node/statement_node/StmtNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/statement_node/internal/CondExprNode.h"

class IfNode : public StmtNode, public std::enable_shared_from_this<IfNode> {
 public:
    const std::shared_ptr<StmtListNode> thenStmtListNode;
    const std::shared_ptr<StmtListNode> elseStmtListNode;
    const std::shared_ptr<CondExprNode> condExprNode;

    IfNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode, std::shared_ptr<StmtListNode> thenStmtListNode,
        std::shared_ptr<StmtListNode> elseStmtListNode);

    void evaluate(IStmtExtractor& extractor) override;
};
