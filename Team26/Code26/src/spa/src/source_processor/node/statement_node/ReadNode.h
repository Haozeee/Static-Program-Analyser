#pragma once

#include <string>
#include <memory>
#include "source_processor/node/statement_node/VariableNameNode.h"

class ReadNode : public VariableNameNode, public std::enable_shared_from_this<ReadNode> {
 public:

    ReadNode(int stmtIndex, std::string varName);

    void evaluate(IStmtExtractor& extractor) override;
};
