#pragma once

#include <string>

class IRelationshipStore {
 public:
    virtual void insertFollowsRelationship(int &previousStmtNo, int &currentStmtNo) = 0;
    virtual void insertParentsRelationship(int &parentStmtNo, int &childStmtNo) = 0;
    virtual void insertUsesSRelationship(int &stmtNo, std::string &variableName) = 0;
    virtual void insertModifiesSRelationship(int &stmtNo, std::string &variableName) = 0;
    virtual void insertUsesPRelationship(std::string  &procedureName, std::string &variableName) = 0;
    virtual void insertModifiesPRelationship(std::string  &procedureName, std::string &variableName) = 0;
};
