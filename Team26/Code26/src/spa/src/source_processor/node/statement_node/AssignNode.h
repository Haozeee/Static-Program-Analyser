#pragma once

#include <string>
#include "StmtNode.h"
#include "source_processor/node/ExprNode.h"

class AssignNode : public StmtNode {
 protected:
    std::string varName;
    ExprNode exprNode;

 public:
    // TODO(oviya): Replace with Expr
    AssignNode(int stmtIndex, std::string varName, ExprNode exprNode);
};
