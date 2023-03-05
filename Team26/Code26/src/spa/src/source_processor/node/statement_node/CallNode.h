#pragma once

#include <string>
#include <memory>
#include "source_processor/node/statement_node/StmtNode.h"

class CallNode : public StmtNode, public std::enable_shared_from_this<CallNode> {
 public:
    const std::string procedureName;

    CallNode(int stmtIndex, std::string processName);

    void evaluate(IStmtExtractor& extractor) override;
};
