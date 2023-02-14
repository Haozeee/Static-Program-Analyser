#pragma once

#include <memory>
#include <string>
#include "StmtNode.h"
#include "source_processor/node/statement_node/StmtNode.h"
#include "source_processor/node/ExprNode.h"

class AssignNode : public StmtNode, public std::enable_shared_from_this<AssignNode> {
 public:
    const std::string varName;
    const std::shared_ptr<ExprNode> exprNode;

    AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode);

    void evaluate(IStmtExtractor& extractor) override;
    void evaluatePattern(IPatternExtractor& extractor) override;
};
