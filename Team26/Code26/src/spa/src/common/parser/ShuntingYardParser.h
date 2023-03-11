#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include "common/parser/ShuntNode.h"
#include "common/exception/ParserException.h"

class ShuntingYardParser {
 public:
    /**
     * Shunting-Yard Algorithm adapt from multiple online sources.
     *
     * @param expr The input expression assume to be syntactically correct.
     * @return Returns the root node of the AST.
     * */
    static std::shared_ptr<ShuntNode> parse(std::string expr);

    static std::shared_ptr<ShuntNode> parse(std::string expr, const std::shared_ptr<std::unordered_set<std::string>>&
    exprVariables, const std::shared_ptr<std::unordered_set<int>>& exprConstants);
};
