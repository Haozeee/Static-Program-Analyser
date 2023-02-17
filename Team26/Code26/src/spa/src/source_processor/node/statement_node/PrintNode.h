#pragma once

#include <string>
#include <memory>
#include "source_processor/node/statement_node/VariableNameNode.h"

class PrintNode : public VariableNameNode, public std::enable_shared_from_this<PrintNode> {
 public:

    PrintNode(int stmtIndex, std::string varName);

    void evaluate(IStmtExtractor& extractor) override;
};
