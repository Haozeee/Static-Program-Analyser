#pragma once

#include <string>
#include "Token.h"

class StringExpressionToken : public Token {

public:
    explicit StringExpressionToken(std::string value);
};
