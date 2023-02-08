#pragma once

#include <string>
#include "StmtNode.h"

class PrintNode : public StmtNode {
 public:
    std::string varName;

    PrintNode(int stmtIndex, std::string varName);

    void evaluate(AbstractExtractor& extractor) override;
};
