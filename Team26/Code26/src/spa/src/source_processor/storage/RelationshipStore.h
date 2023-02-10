#pragma once

#include "IRelationshipStore.h"
#include <memory>
#include <string>
#include "program_knowledge_base/WriteOnlyStorage.h"

class RelationshipStore : public IRelationshipStore {
 private:
    std::shared_ptr<WriteOnlyStorage> relationshipStorage;

 public:
    explicit RelationshipStore(std::shared_ptr<WriteOnlyStorage> storage);

    void insertFollowsRelationship(int &first_param, int &second_param) override;
    void insertParentsRelationship(int &first_param, int &second_param) override;
    void insertUsesSRelationship(int &first_param, std::string &second_param) override;
    void insertModifiesSRelationship(int &first_param, std::string &second_param) override;
    void insertUsesPRelationship(std::string  &first_param, std::string &second_param) override;
    void insertModifiesPRelationship(std::string  &first_param, std::string &second_param) override;
};
