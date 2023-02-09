#pragma once
#include <string>

class WriteOnlyPatternManager {
 public:
    virtual bool insert(int stmt_no, std::string lhs, std::string rhs) = 0;
};
