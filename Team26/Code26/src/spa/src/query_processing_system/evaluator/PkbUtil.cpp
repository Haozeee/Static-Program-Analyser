#include "PkbUtil.h"

EntitySet PkbUtil::getEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return storage->getVariableManager()->getAllEntitiesEntries();
        case DesignEntity::ASSIGN:
            return intSetToStringSet(storage->getAssignManager()->getAllEntitiesEntries());
        case DesignEntity::STMT:
            return intSetToStringSet(storage->getStmtManager()->getAllEntitiesEntries());
        case DesignEntity::PROCEDURE:
            return storage->getProcedureManager()->getAllEntitiesEntries();
        case DesignEntity::READ:
            return intSetToStringSet(storage->getReadManager()->getAllEntitiesEntries());
        case DesignEntity::CONSTANT:
            return intSetToStringSet(storage->getConstantManager()->getAllEntitiesEntries());
        case DesignEntity::PRINT:
            return intSetToStringSet(storage->getPrintManager()->getAllEntitiesEntries());
        case DesignEntity::IF:
            return intSetToStringSet(storage->getIfManager()->getAllEntitiesEntries());
        case DesignEntity::CALL:
            return intSetToStringSet(storage->getCallManager()->getAllEntitiesEntries());
        case DesignEntity::WHILE:
            return {};
        case DesignEntity::NONE:
            return {};
    }
}

EntitySet PkbUtil::intSetToStringSet(std::unordered_set<int> intSet) {
    EntitySet result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}

