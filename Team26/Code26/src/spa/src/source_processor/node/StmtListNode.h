#pragma once

#include "statement_node/StmtNode.h"
#include <memory>
#include <vector>

class StmtListNode : public Node {
 protected:
    std::vector<std::unique_ptr<StmtNode>> stmtList;

 public:
    StmtListNode(std::vector<std::unique_ptr<StmtNode>> stmtList);
};
