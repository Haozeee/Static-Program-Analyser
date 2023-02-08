#pragma once

#include <memory>
#include "StmtNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/StmtListNode.h"

class WhileNode : public StmtNode {
 public:
     std::shared_ptr<CondExprNode> condExprNode;
     std::shared_ptr<StmtListNode> stmtListNode;

     WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode, std::shared_ptr<StmtListNode> stmtListNode);

     void evaluate(AbstractExtractor& extractor) override;
};
