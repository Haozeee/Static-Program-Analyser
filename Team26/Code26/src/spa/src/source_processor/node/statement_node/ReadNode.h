#pragma once

#include <string>
#include "source_processor/node/statement_node/StmtNode.h"

class ReadNode : public StmtNode, public std::enable_shared_from_this<ReadNode> {
 public:
    const std::string varName;

    ReadNode(int stmtIndex, std::string varName);

    void evaluate(IStmtExtractor& extractor) override;
};
