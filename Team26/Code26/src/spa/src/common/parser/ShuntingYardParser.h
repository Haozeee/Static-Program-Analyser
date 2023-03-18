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

    static std::shared_ptr<ShuntNode> parse(std::string expr,
                                            const std::shared_ptr<std::unordered_set<std::string>>& exprVariables,
                                            const std::shared_ptr<std::unordered_set<int>>& exprConstants);

 private:
    static inline std::unordered_map<char, int> ranking = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'%', 2}
    };
    static inline std::vector<std::string> ops = {"+", "-", "*", "/", "%", "(" , ")"};

    static void parseDigit(std::string expr, int& i, bool& isPrevFactor,
                           std::stack<std::shared_ptr<ShuntNode>>& result);
    static void parseDigit(const std::shared_ptr<std::unordered_set<int>>& exprConstants,
                           std::string expr, int& i, bool& isPrevFactor,
                           std::stack<std::shared_ptr<ShuntNode>>& result);

    static void parseVariable(std::string expr, int& i, bool& isPrevFactor,
                              std::stack<std::shared_ptr<ShuntNode>>& result);
    static void parseVariable(const std::shared_ptr<std::unordered_set<std::string>>& exprVariables,
                              std::string expr, int& i, bool& isPrevFactor,
                              std::stack<std::shared_ptr<ShuntNode>>& result);

    static void parseOperatorOrBracket(char c, std::stack<char>& opStack, bool& isPrevFactor,
                                      std::stack<std::shared_ptr<ShuntNode>>& result);

    static void processOperator(std::stack<char>& opStack, std::stack<std::shared_ptr<ShuntNode>>& result);
};
