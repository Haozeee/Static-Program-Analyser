#pragma once

#include <string>
#include "source_processor/node/statement_node/StmtNode.h"

class CallNode : public StmtNode, public std::enable_shared_from_this<CallNode> {
 public:
    const std::string processName;

    CallNode(int stmtIndex, std::string processName);

    void evaluate(IStmtExtractor& extractor) override;
};
