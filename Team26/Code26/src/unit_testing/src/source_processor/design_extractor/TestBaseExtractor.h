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
    std::vector<int> getExprIntegerList() {
        return  this->exprIntegerList;
    }
    std::vector<std::string> getExprVariableList() {
        return this->exprVariableList;
    }

    auto testClearExprStack() {
        return clearExprStack();
    }

    auto testExtractExpr(std::shared_ptr<ExprNode> node) {
        return extractExpr(std::move(node));
    }
};
