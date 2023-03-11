#pragma once

#include <string>
#include <memory>
#include "source_processor/node/statement_node/AssignNode.h"

class IPatternStore {
 public:
    virtual void insertExpressionPattern(std::shared_ptr<AssignNode> node) = 0;
    virtual void insertCondExpressionIfStatement(int stmtIndex, std::string variableName) = 0;
    virtual void insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) = 0;

    virtual void invokePostReverseRelationship() = 0;
};
