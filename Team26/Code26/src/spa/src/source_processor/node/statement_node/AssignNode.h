#pragma once

#include <string>
#include "StmtNode.h"
#include "source_processor/node/ExprNode.h"

class AssignNode : public StmtNode {
 public:
    std::string varName;
    ExprNode exprNode;

    // TODO(oviya): Replace with Expr
    AssignNode(int stmtIndex, std::string varName, ExprNode exprNode);

    void evaluate(AbstractSyntaxTreeExtractor& extractor) override;
};
