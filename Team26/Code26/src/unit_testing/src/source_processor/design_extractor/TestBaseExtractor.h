#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"

class TestBaseExtractor : public BaseExtractor {
 public:
    int getStatementNumber() {
        return currentStmtNo;
    }

    std::vector<std::string> getExprVariableList() {
        return this->exprVariableList;
    }

    auto testClearExprStack() {
        return clearExprStack();
    }
};
