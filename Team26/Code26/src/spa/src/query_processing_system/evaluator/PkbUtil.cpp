#include "PkbUtil.h"

stringEntitySet PkbUtil::intSetToStringSet(std::unordered_set<int> intSet) {
    stringEntitySet result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}


std::unordered_map<std::string, std::unordered_set<std::string>>
PkbUtil::intMapTostringMap(std::unordered_map<int, std::unordered_set<int>> intMap) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    for (auto const& [k, v] : intMap) {
        res.insert({std::to_string(k), PkbUtil::intSetToStringSet(v)});
    }
    return res;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
PkbUtil::intStringMapTostringMap(std::unordered_map<int, std::unordered_set<std::string>> intMap) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    for (auto const& [k, v] : intMap) {
        res.insert({std::to_string(k), v});
    }
    return res;
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
