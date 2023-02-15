#include <utility>

#include "source_processor/design_extractor/extractor/BaseExtractor.h"

class TestBaseExtractor : public BaseExtractor {
//    int currentStmtNo = -1;
//    std::vector<int> exprIntegerList;
//    std::vector<std::string> exprVariableList;
 public:
    int getStatementNumber() {
        return currentStmtNo;
    }
    std::vector<int> getExprIntegerList() {
        return  this->exprIntegerList;
    }
    std::vector<std::string> getExprVariableList() {
        return this->exprVariableList;
    };

    auto testClearExprStack() {
        return clearExprStack();
    }

    auto testExtractExpr(std::shared_ptr<ExprNode> node) {
        return extractExpr(std::move(node));
    }
};
