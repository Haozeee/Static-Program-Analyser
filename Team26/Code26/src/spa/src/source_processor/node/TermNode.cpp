#include "TermNode.h"

TermNode::TermNode(std::shared_ptr<Factor> factor, std::optional<std::pair<TermOperatorType,
    std::shared_ptr<TermNode>>> optionalParams)
    : factor(factor), optionalParams(optionalParams) {}
