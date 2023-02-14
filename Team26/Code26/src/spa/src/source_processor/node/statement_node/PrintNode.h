#pragma once

#include <string>
#include "source_processor/node/statement_node/StmtNode.h"

class PrintNode : public StmtNode, public std::enable_shared_from_this<PrintNode> {
 public:
    const std::string varName;

    PrintNode(int stmtIndex, std::string varName);

    void evaluate(IStmtExtractor& extractor) override;
};
