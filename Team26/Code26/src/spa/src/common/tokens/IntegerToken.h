#pragma once

#include "Token.h"

#include <string>


class IntegerToken : public Token {
public:
    IntegerToken(std::string value);
};