#pragma once

#include <string>
#include "source_processor/node/statement_node/StmtNode.h"

class CallNode : public StmtNode {
 public:
    std::string processName;

    CallNode(int stmtIndex, std::string processName);

    void evaluate(IStmtExtractor& extractor) override;
};
