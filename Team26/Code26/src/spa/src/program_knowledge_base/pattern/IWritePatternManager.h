#pragma once
#include <string>

class IWritePatternManager {
 public:
    virtual bool insertPattern(int stmt_no, std::string left, std::shared_ptr<ShuntNode> right) = 0;
};
