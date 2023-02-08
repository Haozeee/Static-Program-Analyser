#pragma once

#include <string>
#include "Token.h"


class NameToken : public Token {
 public:
    explicit NameToken(std::string value);
};
