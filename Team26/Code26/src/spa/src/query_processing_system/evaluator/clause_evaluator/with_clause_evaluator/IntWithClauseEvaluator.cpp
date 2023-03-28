#include "IntWithClauseEvaluator.h"

IntWithClauseEvaluator::IntWithClauseEvaluator(Reference left, Reference right)
    : WithClauseEvaluator<int>(left, right) {}

EntitySet IntWithClauseEvaluator::getTranslatedValues(int value, DesignEntity de) {
    return {std::to_string(value)};
}

StmtSet IntWithClauseEvaluator::getLeftRefValues() {
    return getRefValue(storage, leftRef);
}

StmtSet IntWithClauseEvaluator::getRightRefValues() {
    return getRefValue(storage, rightRef);
}

StmtSet IntWithClauseEvaluator::getRefValue(ProgrammeStore storage, Reference ref) {
    return std::visit(overload{
            [](const int& i) -> StmtSet { return {i}; },
            [](const std::string& i) -> StmtSet { return {stoi(i)}; },
            [storage](const AttributeReference i) ->
                StmtSet { return storage->getIntEntitiesFromPkb(i.getDesignEntity()); }
    }, ref.getValue());
}
