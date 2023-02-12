#pragma once

#include <string>

class IRelationshipStore {
 public:
    virtual void insertFollowsRelationship(int &first_param, int &second_param) = 0;
    virtual void insertParentsRelationship(int &first_param, int &second_param) = 0;
    virtual void insertUsesSRelationship(int &first_param, std::string &second_param) = 0;
    virtual void insertModifiesSRelationship(int &first_param, std::string &second_param) = 0;
    virtual void insertUsesPRelationship(std::string  &first_param, std::string &second_param) = 0;
    virtual void insertModifiesPRelationship(std::string  &first_param, std::string &second_param) = 0;
};
