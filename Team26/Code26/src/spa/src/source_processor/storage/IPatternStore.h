#pragma once

#include <string>

class IPatternStore {
 public:
    virtual void insertExpressionPattern(std::string &expr) = 0;
};
