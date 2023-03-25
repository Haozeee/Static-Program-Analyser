#include "MockIntIntClauseEvaluator.h"

MockIntIntClauseEvaluator::MockIntIntClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>>
MockIntIntClauseEvaluator::getRelationshipMap() {
    std::unordered_map<int, std::unordered_set<int>> res {
            {1, {2, 3}},
            {3, {4}},
            {4, {5, 6, 7}}
    };
    return res;
}

std::unordered_map<int, std::unordered_set<int>>
MockIntIntClauseEvaluator::getOppositeRelationshipManager() {
    std::unordered_map<int, std::unordered_set<int>> res {
            {2, {1}},
            {3, {1}},
            {4, {3}},
            {5, {4}},
            {6, {4}},
            {7, {4}},
    };
    return res;
}

std::shared_ptr<ResultTable> MockIntIntClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
