#include "RelationshipStore.h"

RelationshipStore::RelationshipStore(std::shared_ptr<WriteOnlyStorage> storage) : relationshipStorage(storage) {
}


void RelationshipStore::insertFollowsRelationship(int &first_param, int &second_param) {
}

void RelationshipStore::insertParentsRelationship(int &first_param, int &second_param) {
}

void RelationshipStore::insertUsesSRelationship(int &first_param, int &second_param) {
}

void RelationshipStore::insertModifiesSRelationship(int &first_param, int &second_param) {
}

