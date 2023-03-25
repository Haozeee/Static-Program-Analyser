#include "IntWithClauseEvaluator.h"

IntWithClauseEvaluator::IntWithClauseEvaluator(Reference left, Reference right)
    : WithClauseEvaluator<int>(left, right) {}

StringSet IntWithClauseEvaluator::getTranslatedValues(int value, DesignEntity de) {
    return {std::to_string(value)};
}

IntSet IntWithClauseEvaluator::getLeftRefValues() {
    return getRefValue(storage, leftRef);
}

IntSet IntWithClauseEvaluator::getRightRefValues() {
    return getRefValue(storage, rightRef);
}

IntSet IntWithClauseEvaluator::getRefValue(StoragePointer storage, Reference ref) {
    return std::visit(overload{
            [](const int& i) -> IntSet { return {i}; },
            [](const std::string& i) -> IntSet { return {stoi(i)}; },
            [storage](const AttributeReference i) ->
                IntSet { return PkbUtil::getIntEntitiesFromPkb(storage, i.getDesignEntity()); }
    }, ref.getValue());
}
