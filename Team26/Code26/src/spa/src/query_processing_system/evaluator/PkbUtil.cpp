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
            return StorageUtil::getEntityValues(storage->getVariableManager());
        case DesignEntity::PROCEDURE:
            return StorageUtil::getEntityValues(storage->getProcedureManager());
        case DesignEntity::CALL:
            // Get all procedures called by call statements
            return StorageUtil::getEntityValues(storage->getCallProcedureManager());
        case DesignEntity::READ:
            // Get all read variables statements
            return StorageUtil::getEntityValues(storage->getReadVariableManager());
        case DesignEntity::PRINT:
            // Get all variables in print statements
            return StorageUtil::getEntityValues(storage->getPrintVariableManager());
        default:
            return {};
    }
}

std::unordered_set<int> PkbUtil::getIntEntitiesFromPkb(std::shared_ptr<ReadStorage> storage, DesignEntity entity) {
    switch (entity) {
        case DesignEntity::ASSIGN:
            return StorageUtil::getEntityValues(storage->getAssignManager());
        case DesignEntity::STMT:
            return StorageUtil::getEntityValues(storage->getStmtManager());
        case DesignEntity::READ:
            return StorageUtil::getEntityValues(storage->getReadStmtNoManager());
        case DesignEntity::CONSTANT:
            return StorageUtil::getEntityValues(storage->getConstantManager());
        case DesignEntity::PRINT:
            return StorageUtil::getEntityValues(storage->getPrintStmtNoManager());
        case DesignEntity::IF:
            return StorageUtil::getEntityValues(storage->getIfManager());
        case DesignEntity::CALL:
            return StorageUtil::getEntityValues(storage->getCallStmtNoManager());
        case DesignEntity::WHILE:
            return StorageUtil::getEntityValues(storage->getWhileManager());
        default:
            return {};
    }
}
