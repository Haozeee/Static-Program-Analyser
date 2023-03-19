#pragma once

#include <memory>
#include <string>

template <typename T, typename U>
class IWritePatternManager {
 public:
    virtual bool insertPattern(int stmtNo, T left, U right) = 0;
};
