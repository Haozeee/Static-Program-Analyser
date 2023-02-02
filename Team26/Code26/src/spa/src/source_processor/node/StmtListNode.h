#pragma once

#include <memory>
#include <vector>
#include "statement_node/StmtNode.h"

class StmtListNode : public Node {
 protected:
    std::vector<std::shared_ptr<StmtNode>> stmtList;

 public:
    explicit StmtListNode(std::vector<std::shared_ptr<StmtNode>> stmtList);
};
