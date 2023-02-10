#pragma once

#include <memory>
#include <string>
#include "StmtNode.h"
#include "source_processor/node/ExprNode.h"

class AssignNode : public StmtNode {
 public:
    std::string varName;
    std::shared_ptr<ExprNode> exprNode;

    AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode);

    void evaluate(AbstractExtractor& extractor) override;
};
