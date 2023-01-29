#pragma once

#include "Token.h"

#include <string>


class NameToken : public Token {
 public:
    NameToken(std::string value);
};
