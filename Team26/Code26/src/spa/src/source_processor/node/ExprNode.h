#pragma once

#include <string>
#include <variant>
#include "Node.h"

using Factor = std::variant<std::string, int>;

class ExprNode : public Node {
 protected:
	Factor expr;
	// TODO(oviya)

 public:
	// TODO(oviya): Replace with Expr, add operator==
	ExprNode(Factor expr);
};
