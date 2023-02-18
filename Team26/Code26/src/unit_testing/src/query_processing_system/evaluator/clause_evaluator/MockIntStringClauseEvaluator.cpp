#include "MockIntStringClauseEvaluator.h"

MockIntStringClauseEvaluator::MockIntStringClauseEvaluator(Argument left, Argument right)
    : IntStringClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<std::string>>
MockIntStringClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    std::unordered_map<int, std::unordered_set<std::string>> res {
            {1, {"v1", "v2"}},
            {3, {"v1"}},
            {4, {"v4", "v5", "v6"}}
    };
    return res;
}

std::unordered_map<std::string, std::unordered_set<int>>
MockIntStringClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    std::unordered_map<std::string , std::unordered_set<int>> res;
    return res;
}

std::shared_ptr<ResultTable> MockIntStringClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}