#include "RelationshipStore.h"
#include <utility>

RelationshipStore::RelationshipStore(std::shared_ptr<WriteStorage> storage) {
    followsManager = storage->getFollowsManager();
    followsTManager = storage->getFollowsTManager();

    parentsManager = storage->getParentManager();
    parentsTManager = storage->getParentTManager();

    usesSManager = storage->getUsesSManager();
    usesPManager = storage->getUsesPManager();

    modifiesSManager = storage->getModifiesSManager();
    modifiesPManager = storage->getModifiesPManager();

    nextManager = storage->getNextManager();

    callSManager = storage->getCallsSManager();
    callPManager = storage->getCallsPManager();
    callsTManager = storage->getCallsTManager();
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

void RelationshipStore::invokeReverseRelationship() {
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


