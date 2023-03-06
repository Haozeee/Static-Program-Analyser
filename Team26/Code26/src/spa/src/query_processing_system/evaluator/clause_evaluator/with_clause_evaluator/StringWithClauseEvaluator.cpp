#include "StringWithClauseEvaluator.h"

StringWithClauseEvaluator::StringWithClauseEvaluator(Reference left, Reference right)
    : WithClauseEvaluator<std::string>(left, right) {}

StringSet StringWithClauseEvaluator::getTranslatedValues(StoragePointer storage, std::string value, DesignEntity de) {
    switch (de) {
        case DesignEntity::CALL:
            return getCallStatements(storage, value);
        case DesignEntity::PRINT:
            return getPrintStatements(storage, value);
        case DesignEntity::READ:
            return getReadStatements(storage, value);
        default:
            return {value};
    }
}

StringSet StringWithClauseEvaluator::getLeftRefValues(StoragePointer storage) {
    return getRefValue(storage, leftRef);
}

StringSet StringWithClauseEvaluator::getRightRefValues(StoragePointer storage) {
    return getRefValue(storage, rightRef);
}

StringSet StringWithClauseEvaluator::getRefValue(StoragePointer storage, Reference ref) {
    return std::visit(overload{
            [](const int& i) -> StringSet { return {std::to_string(i)}; },
            [](const std::string& i) -> StringSet { return {i}; },
            [storage](const AttributeReference i) ->
                StringSet { return PkbUtil::getStringEntitiesFromPkb(storage, i.getDesignEntity()); }
    }, ref.getValue());
}

StringSet StringWithClauseEvaluator::getReadStatements(StoragePointer storage, std::string value) {
    std::unordered_set<int> res;
    auto relationshipStore = storage->getModifiesSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        auto readStatements = storage->getReadStmtNoManager()->getAllEntitiesEntries();
        PkbUtil::setIntersection(it->second, readStatements, res);
    }
    return PkbUtil::intSetToStringSet(res);
}

StringSet StringWithClauseEvaluator::getPrintStatements(StoragePointer storage, std::string value) {
    std::unordered_set<int> res;
    auto relationshipStore = storage->getUsesSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        auto printStatements = storage->getPrintStmtNoManager()->getAllEntitiesEntries();
        PkbUtil::setIntersection(it->second, printStatements, res);
    }
    return PkbUtil::intSetToStringSet(res);
}

StringSet StringWithClauseEvaluator::getCallStatements(StoragePointer storage, std::string value) {
    std::unordered_set<int> res;
    auto relationshipStore = storage->getCallSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        res = it->second;
    }
    return PkbUtil::intSetToStringSet(res);
}
