#pragma once

#include <string>
#include "Token.h"


class SpecialCharToken : public Token {
 public:
    explicit SpecialCharToken(std::string value);
};
