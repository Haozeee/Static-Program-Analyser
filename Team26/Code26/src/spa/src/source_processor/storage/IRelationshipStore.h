#pragma once

class IRelationshipStore {
 public:
    virtual void insertFollowsRelationship(int &first_param, int &second_param) = 0;
    virtual void insertParentsRelationship(int &first_param, int &second_param) = 0;
    virtual void insertUsesSRelationship(int &first_param, int &second_param) = 0;
    virtual void insertModifiesSRelationship(int &first_param, int &second_param) = 0;
};
