#pragma once

#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <optional>
#include "Node.h"

enum class TermOperatorType {
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    OPERATOR_MOD
};

using Factor = std::variant<std::string, int>;

class TermNode : public Node {
 public:
    std::shared_ptr<Factor> factor;
    std::optional<std::pair<TermOperatorType, std::shared_ptr<TermNode>>> optionalParams;

    TermNode(std::shared_ptr<Factor> factor, std::optional<std::pair<TermOperatorType,
        std::shared_ptr<TermNode>>> optionalParams);
};
