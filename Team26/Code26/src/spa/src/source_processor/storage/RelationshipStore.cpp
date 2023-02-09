#include "RelationshipStore.h"

RelationshipStore::RelationshipStore(std::shared_ptr<WriteOnlyStorage> storage) : relationshipStorage(storage) {
}


void RelationshipStore::insertFollowsRelationship(int &first_param, int &second_param) {
     relationshipStorage->getFollowsManager()->insertRelationship(first_param, second_param,
                                                                  relationshipStorage->getFollowsTManager());
}

void RelationshipStore::insertParentsRelationship(int &first_param, int &second_param) {
    relationshipStorage->getParentManager()->insertRelationship(first_param, second_param,
                                                                relationshipStorage->getParentTManager());
}

void RelationshipStore::insertUsesSRelationship(int &first_param, std::string &second_param) {
    relationshipStorage->getUsesSManager()->insertRelationship(first_param, second_param);
}

void RelationshipStore::insertModifiesSRelationship(int &first_param, std::string &second_param) {
    relationshipStorage->getModifiesSManager()->insertRelationship(first_param, second_param);
}

void RelationshipStore::insertUsesPRelationship(std::string &first_param, std::string &second_param) {
    relationshipStorage->getUsesPManager()->insertRelationship(first_param, second_param);
}

void RelationshipStore::insertModifiesPRelationship(std::string &first_param, std::string &second_param) {
    relationshipStorage->getModifiesPManager()->insertRelationship(first_param, second_param);
}

