#pragma once

#include <memory>
#include <vector>
#include "statement_node/StmtNode.h"

class StmtListNode : public Node {
 protected:
    std::vector<std::unique_ptr<StmtNode>> stmtList;

 public:
    StmtListNode(std::vector<std::unique_ptr<StmtNode>> stmtList);
};
