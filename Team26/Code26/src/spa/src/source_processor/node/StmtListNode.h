#pragma once

#include <memory>
#include <vector>
#include "statement_node/StmtNode.h"

class StmtListNode : public Node {
 public:
    std::vector<std::shared_ptr<StmtNode>> stmtList;

    explicit StmtListNode(std::vector<std::shared_ptr<StmtNode>> stmtList);
};
