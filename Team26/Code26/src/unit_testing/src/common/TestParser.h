#pragma once

#include <memory>
#include <string>
#include <vector>
#include "catch.hpp"
#include "common/parser/AbstractParser.h"

class TestParser : public AbstractParser {
 public:
    explicit TestParser(std::vector<std::shared_ptr<Token>> tokens);
    bool hasNext();
    std::shared_ptr<Token> getNext();
    bool isTypeOf(TokenType type);
    bool isValueOf(const std::string& value);
    std::shared_ptr<Token> parseNext(TokenType type);
    std::shared_ptr<Token> parseNext(const std::string& value);
    void parse();
};
