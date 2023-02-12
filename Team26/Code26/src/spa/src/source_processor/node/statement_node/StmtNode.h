#pragma once

#include "source_processor/node/Node.h"

class IStmtExtractor;
class IPatternExtractor;

enum class StmtType {
    STMT_ASSIGN,
    STMT_CALL,
    STMT_IF,
    STMT_PRINT,
    STMT_READ,
    STMT_WHILE
};

class StmtNode : public Node {
 public:
    int stmtIndex;
    StmtType stmtType;

    virtual void evaluate(IStmtExtractor& extractor) = 0;
    virtual void evaluatePattern(IPatternExtractor& extractor);

    explicit StmtNode(int stmtIndex, StmtType stmtType);
};
