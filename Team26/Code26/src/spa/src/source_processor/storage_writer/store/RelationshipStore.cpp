#include "RelationshipStore.h"
#include <utility>

RelationshipStore::RelationshipStore(const std::shared_ptr<WriteStorage>& writeStorage,
                                     const std::shared_ptr<ReadStorage>& readStorage) {
    followsManager = writeStorage->getFollowsManager();
    followsTManager = writeStorage->getFollowsTManager();

    parentsManager = writeStorage->getParentManager();
    parentsTManager = writeStorage->getParentTManager();

    usesSManager = writeStorage->getUsesSManager();
    usesPManager = writeStorage->getUsesPManager();

    modifiesSManager = writeStorage->getModifiesSManager();
    modifiesPManager = writeStorage->getModifiesPManager();

    nextManager = writeStorage->getNextManager();

    callSManager = writeStorage->getCallsSManager();
    callPManager = writeStorage->getCallsPManager();
    callsTManager = writeStorage->getCallsTManager();

    procedureMangerRead = readStorage->getProcedureManager();
    callsPManagerRead = readStorage->getCallsPManager();
    callsTManagerRead = readStorage->getCallsTManager();
    modifiesPManagerRead = readStorage->getModifiesPManager();
    usesPManagerRead = readStorage->getUsesPManager();
}

void RelationshipStore::insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) {
    followsManager->insertRelationship(previousStmtNo, currentStmtNo);
}

void RelationshipStore::insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) {
    parentsManager->insertRelationship(parentStmtNo, childStmtNo);
}

void RelationshipStore::insertFollowsTRelationship(const int &previousTStmtNo, const int &currentStmtNo) {
    followsTManager->insertRelationship(previousTStmtNo, currentStmtNo);
}

void RelationshipStore::insertParentsTRelationship(const int &parentTStmtNo, const int &childStmtNo) {
    parentsTManager->insertRelationship(parentTStmtNo, childStmtNo);
}

void RelationshipStore::insertUsesSRelationship(const int &stmtNo, const std::string &variableName) {
    usesSManager->insertRelationship(stmtNo, variableName);
}

void RelationshipStore::insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) {
    modifiesSManager->insertRelationship(stmtNo, variableName);
}

void RelationshipStore::insertUsesPRelationship(const std::string &procedureName, const std::string &variableName) {
    usesPManager->insertRelationship(procedureName, variableName);
}

void RelationshipStore::insertModifiesPRelationship(const std::string &procedureName, const std::string &variableName) {
    modifiesPManager->insertRelationship(procedureName, variableName);
}

void RelationshipStore::insertCallsRelationship(const int &stmtNo, const std::string &callerName, const std::string
&calleeName) {
    callSManager->insertRelationship(stmtNo, calleeName);
    callPManager->insertRelationship(callerName, calleeName);
}

void RelationshipStore::insertNextRelationship(int previousStmtNo, int currStmtNo) {
    nextManager->insertRelationship(previousStmtNo, currStmtNo);
}

void RelationshipStore::insertCallsTRelationship(std::string caller, std::string callee) {
    callsTManager->insertRelationship(caller, callee);
}

void RelationshipStore::invokePostReverseRelationship() {
    followsManager->setReverse();
    followsTManager->setReverse();

    parentsManager->setReverse();
    parentsTManager->setReverse();

    usesSManager->setReverse();
    usesPManager->setReverse();

    modifiesSManager->setReverse();
    modifiesPManager->setReverse();

    nextManager->setReverse();

    callSManager->setReverse();
    callPManager->setReverse();
    callsTManager->setReverse();
}

void RelationshipStore::invokePreReverseRelationship() {
    callPManager->setReverse();
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipStore::getCallsPReversedRelationship() {
    return callsPManagerRead->getAllReversedRelationshipEntries();
}

bool RelationshipStore::callsPReadContains(std::string procedureName1, std::string procedureName2) {
    return callsPManagerRead->containsMap(procedureName1, procedureName2);
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipStore::getCallsTRelationship() {
    return callsTManagerRead->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipStore::getModifiesPRelationship() {
    return modifiesPManagerRead->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipStore::getUsesPRelationship() {
    return usesPManagerRead->getAllRelationshipEntries();
}

bool RelationshipStore::procedureEntitiesContains(std::string procedureName) {
    return procedureMangerRead->contains(procedureName);
}

std::unordered_set<std::string> RelationshipStore::getProcedureEntities() {
    return procedureMangerRead->getAllEntitiesEntries();
}


