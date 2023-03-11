#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
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

    static std::tuple<
            std::shared_ptr<ShuntNode>,
            std::unordered_set<std::string>,
            std::unordered_set<int>> parsePlus(std::string expr);
};
