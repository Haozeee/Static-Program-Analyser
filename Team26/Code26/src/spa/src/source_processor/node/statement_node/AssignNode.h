#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_set>
#include "StmtNode.h"
#include "source_processor/node/statement_node/VariableNameNode.h"
#include "source_processor/node/ExprNode.h"
#include "common/parser/ShuntNode.h"

class AssignNode : public VariableNameNode, public std::enable_shared_from_this<AssignNode> {
 public:
//    const std::shared_ptr<ExprNode> exprNode;
    const std::shared_ptr<ShuntNode> shutNode;
    const std::unordered_set<std::string> exprVariables;
    const std::unordered_set<int> exprConstants;

    AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ShuntNode> shutNode,
               std::unordered_set<std::string> exprVariables,
               std::unordered_set<int> exprConstants);

    void evaluate(IStmtExtractor& extractor) override;
};
