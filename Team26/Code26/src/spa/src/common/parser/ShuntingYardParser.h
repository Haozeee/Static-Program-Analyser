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
    static std::shared_ptr<ShuntNode> parse(std::string expr) {
        std::stack<std::shared_ptr<ShuntNode>> result;
        std::stack<char> opStack;
        std::unordered_map<char, int> ranking;
        std::vector<std::string> ops{"+", "-", "*", "/", "%", "(" , ")"};
        ranking['+'] = 1;
        ranking['-'] = 1;
        ranking['*'] = 2;
        ranking['/'] = 2;
        ranking['%'] = 2;

        bool isPrevFactor = false;

        for (int i = 0; i < expr.size(); ++i) {
            const char c = expr[i];
            if (isspace(c)) {
                continue;
            } else if (std::isdigit(c)) /* constant */ {
                if (isPrevFactor) {
                    throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
                }
                int k = i;
                while (k < expr.size() && std::isdigit(expr[k])) {
                    ++k;
                }
                std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
                result.push(node);
                i = k - 1;
                isPrevFactor = true;
            } else if (std::isalpha(c)) /* variable */ {
                if (isPrevFactor) {
                    throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
                }
                int k = i;
                while (k < expr.size() && std::isalnum(expr[k])) {
                    ++k;
                }
                std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
                result.push(node);
                i = k - 1;
                isPrevFactor = true;
            } else if (std::find(ops.begin(),
                                 ops.end(),
                                 std::string(1, c)) != ops.end()) /* operator or bracket */ {
                if (c == '(') {
                    opStack.push(c);
                } else if (c == ')') {
                    while (!opStack.empty() && opStack.top() != '(') {
                        if (result.size() < 2) {
                            throw ShuntingYardParserException(
                                    ParserShuntingYardParserInvalidExpressionExceptionMessage);
                        }

                        std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
                        opStack.pop();
                        node->right = result.top();
                        result.pop();
                        node->left = result.top();
                        result.pop();
                        result.push(node);
                    }
                    if (opStack.empty()) {
                        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
                    }
                    opStack.pop();

                } else {
                    while (!opStack.empty() && ranking[opStack.top()] >= ranking[c]) {
                        if (result.size() < 2) {
                            throw ShuntingYardParserException(
                                    ParserShuntingYardParserInvalidExpressionExceptionMessage);
                        }

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
                isPrevFactor = false;
            } else {
                throw ShuntingYardParserException(
                        ParserShuntingYardParserUnknownOperatorExceptionMessage);
            }
        }

        while (!opStack.empty()) {
            if (result.size() < 2) {
                throw ShuntingYardParserException(
                        ParserShuntingYardParserInvalidExpressionExceptionMessage);
            }

            std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
            opStack.pop();
            node->right = result.top();
            result.pop();
            node->left = result.top();
            result.pop();
            result.push(node);
        }

        if (result.size() != 1) {
            throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
        }

        return result.top();
    }
};
