#include "RelationshipStore.h"

RelationshipStore::RelationshipStore(std::shared_ptr<WriteOnlyStorage> storage) : relationshipStorage(storage) {
}


void RelationshipStore::insertFollowsRelationship(int &first_param, int &second_param) {
     relationshipStorage->getFollowsManager()->insertRelationship(first_param, second_param,
                                                                  relationshipStorage->getFollowsTManager());
}

void RelationshipStore::insertParentsRelationship(int &first_param, int &second_param) {
}

void RelationshipStore::insertUsesSRelationship(int &first_param, int &second_param) {
}

void RelationshipStore::insertModifiesSRelationship(int &first_param, int &second_param) {
}

