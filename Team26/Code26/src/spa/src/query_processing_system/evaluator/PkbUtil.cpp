#include "PkbUtil.h"

stringEntitySet PkbUtil::getEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return storage->getVariableManager()->getAllEntitiesEntries();
        case DesignEntity::PROCEDURE:
            return storage->getProcedureManager()->getAllEntitiesEntries();
        default:
            return PkbUtil::intSetToStringSet(PkbUtil::getStatementEntitiesFromPkb(storage, entity));
    }
}

intEntitySet PkbUtil::getStatementEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity) {
    switch (entity) {
        case DesignEntity::ASSIGN:
            return storage->getAssignManager()->getAllEntitiesEntries();
        case DesignEntity::STMT:
            return storage->getStmtManager()->getAllEntitiesEntries();
        case DesignEntity::READ:
            return storage->getReadManager()->getAllEntitiesEntries();
        case DesignEntity::CONSTANT:
            return storage->getConstantManager()->getAllEntitiesEntries();
        case DesignEntity::PRINT:
            return storage->getPrintManager()->getAllEntitiesEntries();
        case DesignEntity::IF:
            return storage->getIfManager()->getAllEntitiesEntries();
        case DesignEntity::CALL:
            return storage->getCallManager()->getAllEntitiesEntries();
        case DesignEntity::WHILE:
            return {};
        default:
            return {};
    }
}

stringEntitySet PkbUtil::intSetToStringSet(std::unordered_set<int> intSet) {
    stringEntitySet result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}

