#pragma once

#include <string>
#include "StmtNode.h"

class CallNode : public StmtNode {
 public:
    std::string processName;

    CallNode(int stmtIndex, std::string processName);

    void evaluate(AbstractExtractor& extractor) override;
};
