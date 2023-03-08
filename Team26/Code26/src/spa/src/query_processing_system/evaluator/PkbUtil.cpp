#include "PkbUtil.h"
#include "Util.h"

std::unordered_set<std::string> PkbUtil::getEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                            DesignEntity entity) {
    if (entity == DesignEntity::VARIABLE || entity == DesignEntity::PROCEDURE) {
        return PkbUtil::getStringEntitiesFromPkb(storage, entity);
    } else {
        return Util::intSetToStringSet(PkbUtil::getIntEntitiesFromPkb(storage, entity));
    }
}

std::unordered_set<std::string> PkbUtil::getStringEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                                  DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return storage->getVariableManager()->getAllEntitiesEntries();
        case DesignEntity::PROCEDURE:
            return storage->getProcedureManager()->getAllEntitiesEntries();
        case DesignEntity::CALL:
            // Get all procedures called by call statements
            return storage->getCallProcedureManager()->getAllEntitiesEntries();
        case DesignEntity::READ:
            // Get all read variables statements
            return storage->getReadVariableManager()->getAllEntitiesEntries();
        case DesignEntity::PRINT:
            // Get all variables in print statements
            return storage->getPrintVariableManager()->getAllEntitiesEntries();
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
            return storage->getReadStmtNoManager()->getAllEntitiesEntries();
        case DesignEntity::CONSTANT:
            return storage->getConstantManager()->getAllEntitiesEntries();
        case DesignEntity::PRINT:
            return storage->getPrintStmtNoManager()->getAllEntitiesEntries();
        case DesignEntity::IF:
            return storage->getIfManager()->getAllEntitiesEntries();
        case DesignEntity::CALL:
            return storage->getCallStmtNoManager()->getAllEntitiesEntries();
        case DesignEntity::WHILE:
            return storage->getWhileManager()->getAllEntitiesEntries();
        default:
            return {};
    }
}
