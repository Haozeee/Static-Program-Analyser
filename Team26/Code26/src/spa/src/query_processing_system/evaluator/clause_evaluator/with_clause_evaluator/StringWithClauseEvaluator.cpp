#include "StringWithClauseEvaluator.h"

StringWithClauseEvaluator::StringWithClauseEvaluator(Reference left, Reference right)
    : WithClauseEvaluator<std::string>(left, right) {}

EntitySet StringWithClauseEvaluator::getTranslatedValues(std::string value, DesignEntity de) {
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

EntitySet StringWithClauseEvaluator::getLeftRefValues() {
    return getRefValue(storage, leftRef);
}

EntitySet StringWithClauseEvaluator::getRightRefValues() {
    return getRefValue(storage, rightRef);
}

EntitySet StringWithClauseEvaluator::getRefValue(StoragePointer storage, Reference ref) {
    return std::visit(overload{
            [](const int& i) -> EntitySet { return {std::to_string(i)}; },
            [](const std::string& i) -> EntitySet { return {i}; },
            [storage](const AttributeReference i) ->
                EntitySet { return PkbUtil::getStringEntitiesFromPkb(storage, i.getDesignEntity()); }
    }, ref.getValue());
}

EntitySet StringWithClauseEvaluator::getReadStatements(StoragePointer storage, std::string value) {
    StmtSet res;
    auto relationshipStore = storage->getModifiesSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        auto readStatements = storage->getReadStmtNoManager()->getAllEntitiesEntries();
        Util::setIntersection(it->second, readStatements, res);
    }
    return Util::intSetToStringSet(res);
}

EntitySet StringWithClauseEvaluator::getPrintStatements(StoragePointer storage, std::string value) {
    StmtSet res;
    auto relationshipStore = storage->getUsesSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        auto printStatements = storage->getPrintStmtNoManager()->getAllEntitiesEntries();
        Util::setIntersection(it->second, printStatements, res);
    }
    return Util::intSetToStringSet(res);
}

EntitySet StringWithClauseEvaluator::getCallStatements(StoragePointer storage, std::string value) {
    StmtSet res;
    auto relationshipStore = storage->getCallsSManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(value);
    if (it != relationshipStore.end()) {
        res = it->second;
    }
    return Util::intSetToStringSet(res);
}
