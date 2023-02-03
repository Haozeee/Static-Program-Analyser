#pragma once

#include <string>
#include <variant>
#include "Node.h"

using Factor = std::variant<std::string, int>;

class ExprNode : public Node {
 public:
    Factor expr;
    // TODO(oviya): Replace with Expr, add operator==
    explicit ExprNode(Factor expr);
};
