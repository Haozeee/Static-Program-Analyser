#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ShuntNode.h"

class ShuntingYardParser {
 public:
    /**
     * Shunting-Yard Algorithm adapt from multiple online sources.
     *
     * @param expr The input expression assume to be syntactically correct.
     * @return Returns the root node of the AST.
     * */
    static std::shared_ptr<ShuntNode> parse(std::string expr) {
        std::stack<std::shared_ptr<ShuntNode>> result;
        std::stack<char> opStack;
        std::unordered_map<char, int> ranking;
        ranking['+'] = 1;
        ranking['-'] = 1;
        ranking['*'] = 2;
        ranking['/'] = 2;
        ranking['%'] = 2;

        for (int i = 0; i < expr.size(); ++i) {
            const char c = expr[i];

            if (std::isdigit(c)) /* constant */ {
                int k = i;
                while (k < expr.size() && std::isdigit(expr[k])) {
                    ++k;
                }
                std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
                result.push(node);
                i = k - 1;
            } else if (std::isalpha(c)) /* variable */ {
                int k = i;
                while (k < expr.size() && std::isalnum(expr[k])) {
                    ++k;
                }
                std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
                result.push(node);
                i = k - 1;
            } else /* operator or bracket */ {
                if (c == '(') {
                    opStack.push(c);
                } else if (c == ')') {
                    while (!opStack.empty() && opStack.top() != '(') {
                        std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
                        opStack.pop();
                        node->right = result.top();
                        result.pop();
                        node->left = result.top();
                        result.pop();
                        result.push(node);
                    }
                    opStack.pop();
                } else {
                    while (!opStack.empty() && ranking[opStack.top()] >= ranking[c]) {
                        std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
                        opStack.pop();
                        node->right = result.top();
                        result.pop();
                        node->left = result.top();
                        result.pop();
                        result.push(node);
                    }
                    opStack.push(c);
                }
            }
        }
        while (!opStack.empty()) {
            std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
            opStack.pop();
            node->right = result.top();
            result.pop();
            node->left = result.top();
            result.pop();
            result.push(node);
        }
        return result.top();
    }
};

