#include "StorageReader.h"

StorageReader::StorageReader(std::shared_ptr<ReadStorage> pkbStorage_)
    : pkbStorage(pkbStorage_), cacheStorage(std::make_shared<Cache>(pkbStorage_)) {}

EntitySet StorageReader::getStringEntitiesFromPkb(DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return StorageUtil::getEntityValues(pkbStorage->getVariableManager());
        case DesignEntity::PROCEDURE:
            return StorageUtil::getEntityValues(pkbStorage->getProcedureManager());
        case DesignEntity::CALL:
            // Get all procedures called by call statements
            return StorageUtil::getEntityValues(pkbStorage->getCallProcedureManager());
        case DesignEntity::READ:
            // Get all read variables statements
            return StorageUtil::getEntityValues(pkbStorage->getReadVariableManager());
        case DesignEntity::PRINT:
            // Get all variables in print statements
            return StorageUtil::getEntityValues(pkbStorage->getPrintVariableManager());
        default:
            return {};
    }
}

StmtSet StorageReader::getIntEntitiesFromPkb(DesignEntity entity) {
    switch (entity) {
        case DesignEntity::ASSIGN:
            return StorageUtil::getEntityValues(pkbStorage->getAssignManager());
        case DesignEntity::STMT:
            return StorageUtil::getEntityValues(pkbStorage->getStmtManager());
        case DesignEntity::READ:
            return StorageUtil::getEntityValues(pkbStorage->getReadStmtNoManager());
        case DesignEntity::CONSTANT:
            return StorageUtil::getEntityValues(pkbStorage->getConstantManager());
        case DesignEntity::PRINT:
            return StorageUtil::getEntityValues(pkbStorage->getPrintStmtNoManager());
        case DesignEntity::IF:
            return StorageUtil::getEntityValues(pkbStorage->getIfManager());
        case DesignEntity::CALL:
            return StorageUtil::getEntityValues(pkbStorage->getCallStmtNoManager());
        case DesignEntity::WHILE:
            return StorageUtil::getEntityValues(pkbStorage->getWhileManager());
        default:
            return {};
    }
}

EntitySet StorageReader::getEntitiesFromPkb(DesignEntity entity) {
    if (entity == DesignEntity::VARIABLE || entity == DesignEntity::PROCEDURE) {
        return getStringEntitiesFromPkb(entity);
    } else {
        return Util::intSetToStringSet(getIntEntitiesFromPkb(entity));
    }
}

StmtStmtMap StorageReader::getFollowsMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getFollowsManager());
}

StmtStmtMap StorageReader::getFollowsTMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getFollowsTManager());
}

StmtStmtMap StorageReader::getParentMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getParentManager());
}

StmtStmtMap StorageReader::getParentTMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getParentTManager());
}

StmtStmtMap StorageReader::getNextMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getNextManager());
}

StmtStmtMap StorageReader::getNextTMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cacheStorage->getNextTCache(), interestedValues);
}

StmtStmtMap StorageReader::getAffectsMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cacheStorage->getAffectsCache(), interestedValues);
}

StmtStmtMap StorageReader::getAffectsTMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cacheStorage->getAffectsTCache(), interestedValues);
}

StmtEntityMap StorageReader::getUsesSMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getUsesSManager());
}

StmtEntityMap StorageReader::getModifiesSMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getModifiesSManager());
}

EntityEntityMap StorageReader::getUsesPMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getUsesPManager());
}

EntityEntityMap StorageReader::getModifiesPMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getModifiesPManager());
}

EntityEntityMap StorageReader::getCallsMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getCallsPManager());
}

EntityEntityMap StorageReader::getCallsTMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getCallsTManager());
}

StmtEntityMap StorageReader::getCallsSMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(pkbStorage->getCallsSManager());
}

StmtStmtMap StorageReader::getFollowsReverseMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getFollowsManager());
}

StmtStmtMap StorageReader::getFollowsTReverseMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getFollowsTManager());
}

StmtStmtMap StorageReader::getParentReverseMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getParentManager());
}

StmtStmtMap StorageReader::getParentTReverseMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getParentTManager());
}

StmtStmtMap StorageReader::getNextReverseMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getNextManager());
}

StmtStmtMap StorageReader::getNextTReverseMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cacheStorage->getNextTReverseCache(), interestedValues);
}

StmtStmtMap StorageReader::getAffectsReverseMap(StmtSet &interestedValues) {
    return cacheStorage->getAffectsReverseCacheData();
}

StmtStmtMap StorageReader::getAffectsTReverseMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cacheStorage->getAffectsTReverseCache(), interestedValues);
}

EntityStmtMap StorageReader::getUsesSReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getUsesSManager());
}

EntityStmtMap StorageReader::getModifiesSReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getModifiesSManager());
}

EntityEntityMap StorageReader::getUsesPReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getUsesPManager());
}

EntityEntityMap StorageReader::getModifiesPReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getModifiesPManager());
}

EntityEntityMap StorageReader::getCallsReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getCallsPManager());
}

EntityEntityMap StorageReader::getCallsTReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getCallsTManager());
}

EntityStmtMap StorageReader::getCallsSReverseMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getCallsSManager());
}

bool StorageReader::isFollowsEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getFollowsManager());
}

bool StorageReader::isParentEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getParentManager());
}

bool StorageReader::isNextEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getNextManager());
}

bool StorageReader::isAffectsEmpty() {
    return Cache::isCacheEmpty(cacheStorage->getAffectsCache());
}

bool StorageReader::isModifiesSEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getModifiesSManager());
}

bool StorageReader::isUsesSEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getUsesSManager());
}

bool StorageReader::isModifiesPEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getModifiesPManager());
}

bool StorageReader::isUsesPEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getUsesPManager());
}

bool StorageReader::isCallsEmpty() {
    return StorageUtil::isRelationEmpty(pkbStorage->getCallsPManager());
}

StmtEntityMap StorageReader::getAllIfCondEntries() {
    return StorageUtil::getRelationshipMap(pkbStorage->getIfCondManager());
}

EntityStmtMap StorageReader::getAllReverseIfCondEntries() {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getIfCondManager());
}

StmtEntityMap StorageReader::getAllWhileCondEntries() {
    return StorageUtil::getRelationshipMap(pkbStorage->getWhileCondManager());
}

EntityStmtMap StorageReader::getAllReverseWhileCondEntries() {
    return StorageUtil::getReverseRelationshipMap(pkbStorage->getWhileCondManager());
}

AssignStatements StorageReader::getAssignStatementEntries(EntitySet &interestedEntries) {
    AssignStatements results;
    auto assignStatements = StorageUtil::getAllPatternEntries(pkbStorage->getAssignPatternManager());
    auto lhsEntries = StorageUtil::getAllLhsPatternEntries(pkbStorage->getAssignPatternManager());
    auto rhsEntries = StorageUtil::getAllRhsPatternEntries(pkbStorage->getAssignPatternManager());
    for (auto const& [k, v] : assignStatements) {
        // v = real value of the assign statement in the source code
        results.insert({v, {lhsEntries->at(k), rhsEntries->at(k)}});
    }

    return results;
}
