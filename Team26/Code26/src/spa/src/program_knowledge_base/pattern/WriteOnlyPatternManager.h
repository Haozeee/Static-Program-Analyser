#pragma once
#include <string>

class WriteOnlyPatternManager {
 public:
    virtual bool insertPattern(int stmt_no, std::string left, std::string right) = 0;
};
