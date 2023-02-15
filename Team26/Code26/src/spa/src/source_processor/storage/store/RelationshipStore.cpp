#include "RelationshipStore.h"

#include <utility>

RelationshipStore::RelationshipStore(std::shared_ptr<WriteStorage> storage) {
    followsManager = storage->getFollowsManager();
    followsTManager = storage->getFollowsTManager();
    parentManager = storage->getParentManager();
    parentTManager = storage->getParentTManager();
    usesSManager = storage->getUsesSManager();
    modifiesSManager = storage->getModifiesSManager();
    usesPManager = storage->getUsesPManager();
    modifiesPManager = storage->getModifiesPManager();
}


void RelationshipStore::insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) {
    followsManager->insertRelationship(previousStmtNo, currentStmtNo, followsTManager);
}

void RelationshipStore::insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) {
    parentManager->insertRelationship(parentStmtNo, childStmtNo, parentTManager);
}

void RelationshipStore::insertUsesSRelationship(const int &stmtNo, const std::string &variableName) {
    usesSManager->insertRelationship(stmtNo, variableName);
}

void RelationshipStore::insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) {
    modifiesSManager->insertRelationship(stmtNo, variableName);
}

void RelationshipStore::insertUsesPRelationship(std::string &procedureName, const std::string &variableName) {
    usesPManager->insertRelationship(procedureName, variableName);
}

void RelationshipStore::insertModifiesPRelationship(std::string &procedureName, const std::string &variableName) {
    modifiesPManager->insertRelationship(procedureName, variableName);
}

