#pragma once

#include <memory>
#include "source_processor/node/statement_node/StmtNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/statement_node/internal/CondExprNode.h"

class WhileNode : public StmtNode, public std::enable_shared_from_this<WhileNode> {
 public:
    const std::shared_ptr<CondExprNode> condExprNode;
    const std::shared_ptr<StmtListNode> stmtListNode;

    WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode, std::shared_ptr<StmtListNode> stmtListNode);

    void evaluate(IStmtExtractor& extractor) override;
};
