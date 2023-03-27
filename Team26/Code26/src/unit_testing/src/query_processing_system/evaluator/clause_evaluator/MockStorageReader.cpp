#include "MockStorageReader.h"

MockStorageReader::MockStorageReader() = default;

EntitySet MockStorageReader::getStringEntitiesFromPkb(DesignEntity entity) {
    return testEntitySet;
}

StmtSet MockStorageReader::getIntEntitiesFromPkb(DesignEntity entity) {
    return testStmtSet;
}

EntitySet MockStorageReader::getEntitiesFromPkb(DesignEntity entity) {
    return testEntitySet;
}

StmtStmtMap MockStorageReader::getFollowsMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getFollowsTMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getParentMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getParentTMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getNextMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getNextTMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getAffectsMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtStmtMap MockStorageReader::getAffectsTMap(StmtSet &interestedValues) {
    return testStmtStmtMap;
}

StmtEntityMap MockStorageReader::getUsesSMap(StmtSet &interestedValues) {
    return testStmtEntityMap;
}

StmtEntityMap MockStorageReader::getModifiesSMap(StmtSet &interestedValues) {
    return testStmtEntityMap;
}

EntityEntityMap MockStorageReader::getUsesPMap(EntitySet &interestedValues) {
    return testEntityEntityMap;
}

EntityEntityMap MockStorageReader::getModifiesPMap(EntitySet &interestedValues) {
    return testEntityEntityMap;
}

EntityEntityMap MockStorageReader::getCallsMap(EntitySet &interestedValues) {
    return testEntityEntityMap;
}

EntityEntityMap MockStorageReader::getCallsTMap(EntitySet &interestedValues) {
    return testEntityEntityMap;
}

StmtEntityMap MockStorageReader::getCallsSMap(EntitySet &interestedValues) {
    return testStmtEntityMap;
}

StmtStmtMap MockStorageReader::getFollowsReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getFollowsTReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getParentReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getParentTReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getNextReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getNextTReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getAffectsReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

StmtStmtMap MockStorageReader::getAffectsTReverseMap(StmtSet &interestedValues) {
    return testStmtStmtReverseMap;
}

EntityStmtMap MockStorageReader::getUsesSReverseMap(EntitySet &interestedValues) {
    return testEntityStmtMap;
}

EntityStmtMap MockStorageReader::getModifiesSReverseMap(EntitySet &interestedValues) {
    return testEntityStmtMap;
}

EntityEntityMap MockStorageReader::getUsesPReverseMap(EntitySet &interestedValues) {
    return testEntityEntityReverseMap;
}

EntityEntityMap MockStorageReader::getModifiesPReverseMap(EntitySet &interestedValues) {
    return testEntityEntityReverseMap;
}

EntityEntityMap MockStorageReader::getCallsReverseMap(EntitySet &interestedValues) {
    return testEntityEntityReverseMap;
}

EntityEntityMap MockStorageReader::getCallsTReverseMap(EntitySet &interestedValues) {
    return testEntityEntityReverseMap;
}

EntityStmtMap MockStorageReader::getCallsSReverseMap(EntitySet &interestedValues) {
    return testEntityStmtMap;
}

bool MockStorageReader::isFollowsEmpty() {
    return false;
}

bool MockStorageReader::isParentEmpty() {
    return false;
}

bool MockStorageReader::isNextEmpty() {
    return false;
}

bool MockStorageReader::isAffectsEmpty() {
    return false;
}

bool MockStorageReader::isModifiesSEmpty() {
    return false;
}

bool MockStorageReader::isUsesSEmpty() {
    return false;
}

bool MockStorageReader::isModifiesPEmpty() {
    return false;
}

bool MockStorageReader::isUsesPEmpty() {
    return false;
}

bool MockStorageReader::isCallsEmpty() {
    return false;
}

StmtEntityMap MockStorageReader::getAllIfCondEntries() {
    return testStmtEntityMap;
}

EntityStmtMap MockStorageReader::getAllReverseIfCondEntries() {
    return testEntityStmtMap;
}

StmtEntityMap MockStorageReader::getAllWhileCondEntries() {
    return testStmtEntityMap;
}

EntityStmtMap MockStorageReader::getAllReverseWhileCondEntries() {
    return testEntityStmtMap;
}

AssignStatements MockStorageReader::getAssignStatementEntries(EntitySet &interestedEntries) {
    AssignStatements results;
    return results;
}
