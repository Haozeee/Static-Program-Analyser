#include "PkbUtil.h"

stringEntitySet PkbUtil::intSetToStringSet(std::unordered_set<int> intSet) {
    stringEntitySet result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}


std::unordered_set<std::string> PkbUtil::getEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                            DesignEntity entity) {
    if (entity == DesignEntity::VARIABLE || entity == DesignEntity::PROCEDURE) {
        return PkbUtil::getStringEntitiesFromPkb(storage, entity);
    } else {
        return PkbUtil::intSetToStringSet(PkbUtil::getIntEntitiesFromPkb(storage, entity));
    }
}

std::unordered_set<std::string> PkbUtil::getStringEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                                  DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return storage->getVariableManager()->getAllEntitiesEntries();
        case DesignEntity::PROCEDURE:
            return storage->getProcedureManager()->getAllEntitiesEntries();
        default:
            return {};
    }
}

std::unordered_set<int> PkbUtil::getIntEntitiesFromPkb(std::shared_ptr<ReadStorage> storage, DesignEntity entity) {
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
