#pragma once

#include <string>

class IRelationshipStoreBase {
 public:
    virtual void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) = 0;

    virtual void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) = 0;

    virtual void insertFollowsTRelationship(const int &previousTStmtNo, const int &currentStmtNo) = 0;

    virtual void insertParentsTRelationship(const int &parentTStmtNo, const int &childStmtNo) = 0;

    virtual void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) = 0;

    virtual void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) = 0;

    virtual void insertUsesPRelationship(const std::string &procedureName, const std::string &variableName) = 0;

    virtual void insertModifiesPRelationship(const std::string &procedureName, const std::string &variableName) = 0;

    virtual void insertCallsRelationship(const int &stmtNo, const std::string &callerName, const std::string
    &calleeName) = 0;

    virtual void insertCallsTRelationship(std::string caller, std::string callee) = 0;

    virtual void insertNextRelationship(int previousStmtNo, int currStmtNo) = 0;
};
