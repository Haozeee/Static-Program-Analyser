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

            if (std::isdigit(c)) /* constant */ {
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

//static bool isOperatorOrBracket(char c) {
//    std::vector<char> ops{'(', ')', '+', '-', '*', '/', '%'};
//    return std::find(ops.begin(), ops.end(), c) != ops.end();
//}
//
//static std::shared_ptr<ShuntNode> createNode(std::shared_ptr<ShuntNode> left, std::shared_ptr<ShuntNode> right, char op) {
//    auto node = std::make_shared<ShuntNode>(std::string(1, op));
//    node->left = left;
//    node->right = right;
//    return node;
//}
//
//static void applyOperator(std::stack<std::shared_ptr<ShuntNode>>& result, std::stack<char>& opStack, char op) {
//    while (!opStack.empty() && isOperatorOrBracket(opStack.top()) && ((opStack.top() != '(' && opStack.top() != ')') || op != ')') && ranking[opStack.top()] >= ranking[op]) {
//        auto right = result.top();
//        result.pop();
//        auto left = result.top();
//        result.pop();
//        result.push(createNode(left, right, opStack.top()));
//        opStack.pop();
//    }
//    opStack.push(op);
//}
//
//static std::shared_ptr<ShuntNode> parse(std::string expr) {
//    std::stack<std::shared_ptr<ShuntNode>> result;
//    std::stack<char> opStack;
//    std::unordered_map<char, int> ranking{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}};
//
//    for (int i = 0; i < expr.size(); ++i) {
//        const char c = expr[i];
//
//        if (std::isdigit(c)) /* constant */ {
//            int k = i;
//            while (k < expr.size() && std::isdigit(expr[k])) {
//                ++k;
//            }
//            result.push(std::make_shared<ShuntNode>(expr.substr(i, k -i)));
//            i = k - 1;
//        } else if (std::isalpha(c)) /* variable */ {
//            int k = i;
//            while (k < expr.size() && std::isalnum(expr[k])) {
//                ++k;
//            }
//            result.push(std::make_shared<ShuntNode>(expr.substr(i, k -i)));
//            i = k - 1;
//        } else if (isOperatorOrBracket(c)) /* operator or bracket */ {
//            if (c == '(') {
//                opStack.push(c);
//            } else if (c == ')') {
//                applyOperator(result, opStack, c);
//                opStack.pop();
//            } else {
//                applyOperator(result, opStack, c);
//            }
//        } else {
//            throw ShuntingYardParserException(ParserShuntingYardParserUnknownOperatorExceptionMessage);
//        }
//    }
//
//    while (!opStack.empty() && isOperatorOrBracket(opStack.top())) {
//        auto right = result.top();
//        result.pop();
//        auto left = result.top();
//        result.pop();
//        result.push(createNode(left, right, opStack.top()));
//        opStack.pop();
//    }
//
//    if (result.size() != 1 || !opStack.empty()) {
//        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
//    }
//
//    return result.top();
//}

