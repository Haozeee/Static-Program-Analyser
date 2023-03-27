#include "StorageReader.h"

StorageReader::StorageReader(std::shared_ptr<ReadStorage> pkbStorage_, std::shared_ptr<Cache> cacheStorage_)
    : pkbStorage(pkbStorage_), cacheStorage(cacheStorage_) {}

EntitySet StorageReader::getStringEntitiesFromPkb(DesignEntity entity) {
    return EntitySet();
}

StmtSet StorageReader::getIntEntitiesFromPkb(DesignEntity entity) {
    return StmtSet();
}

EntitySet StorageReader::getEntitiesFromPkb(DesignEntity entity) {
    return EntitySet();
}

StmtStmtMap StorageReader::getFollowsMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getFollowsTMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getParentMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getParentTMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getNextMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getNextTMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getAffectsMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getAffectsTMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtEntityMap StorageReader::getUsesSMap(StmtSet &interestedValues) {
    return StmtEntityMap();
}

StmtEntityMap StorageReader::getModifiesSMap(StmtSet &interestedValues) {
    return StmtEntityMap();
}

EntityEntityMap StorageReader::getUsesPMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getModifiesPMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getCallsMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getCallsTMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

StmtEntityMap StorageReader::getCallsSMap(EntitySet &interestedValues) {
    return StmtEntityMap();
}

StmtStmtMap StorageReader::getFollowsReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getFollowsTReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getParentReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getParentTReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getNextReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getNextTReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getAffectsReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

StmtStmtMap StorageReader::getAffectsTReverseMap(StmtSet &interestedValues) {
    return StmtStmtMap();
}

EntityStmtMap StorageReader::getUsesSReverseMap(EntitySet &interestedValues) {
    return EntityStmtMap();
}

EntityStmtMap StorageReader::getModifiesSReverseMap(EntitySet &interestedValues) {
    return EntityStmtMap();
}

EntityEntityMap StorageReader::getUsesPReverseMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getModifiesPReverseMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getCallsReverseMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityEntityMap StorageReader::getCallsTReverseMap(EntitySet &interestedValues) {
    return EntityEntityMap();
}

EntityStmtMap StorageReader::getCallsSReverseMap(EntitySet &interestedValues) {
    return EntityStmtMap();
}

bool StorageReader::isFollowsEmpty() {
    return false;
}

bool StorageReader::isParentEmpty() {
    return false;
}

bool StorageReader::isNextEmpty() {
    return false;
}

bool StorageReader::isAffectsEmpty() {
    return false;
}

bool StorageReader::isModifiesSEmpty() {
    return false;
}

bool StorageReader::isUsesSEmpty() {
    return false;
}

bool StorageReader::isModifiesPEmpty() {
    return false;
}

bool StorageReader::isUsesPEmpty() {
    return false;
}

bool StorageReader::isCallsEmpty() {
    return false;
}

StmtEntityMap StorageReader::getAllIfCondEntries() {
    return StmtEntityMap();
}

EntityStmtMap StorageReader::getAllReverseIfCondEntries() {
    return EntityStmtMap();
}

StmtEntityMap StorageReader::getAllWhileCondEntries() {
    return StmtEntityMap();
}

EntityStmtMap StorageReader::getAllReverseWhileCondEntries() {
    return EntityStmtMap();
}

AssignStatements StorageReader::getAssignStatementEntries(EntitySet &interestedEntries) {
    return ISourceReader::getAssignStatementEntries(interestedEntries);
}
