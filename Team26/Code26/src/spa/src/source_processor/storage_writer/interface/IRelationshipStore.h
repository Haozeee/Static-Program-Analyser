#pragma once

#include <string>
#include <unordered_map>
#include "program_knowledge_base/entity/IReadEntityManager.h"
#include "program_knowledge_base/relationship/IReadRelationshipManager.h"

class IRelationshipStore {
 public:
    virtual void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) = 0;
    virtual void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) = 0;
    virtual void insertFollowsTRelationship(const int &previousTStmtNo, const int &currentStmtNo) = 0;
    virtual void insertParentsTRelationship(const int &parentTStmtNo, const int &childStmtNo) = 0;
    virtual void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) = 0;
    virtual void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) = 0;
    virtual void insertUsesPRelationship(const std::string  &procedureName, const std::string &variableName) = 0;
    virtual void insertModifiesPRelationship(const std::string  &procedureName, const std::string &variableName) = 0;
    virtual void insertCallsRelationship(const int &stmtNo, const std::string &callerName, const std::string
    &calleeName) = 0;
    virtual void insertCallsTRelationship(std::string caller, std::string callee) = 0;
    virtual void insertNextRelationship(int previousStmtNo, int currStmtNo) = 0;

    virtual void invokePostReverseRelationship() = 0;
    virtual void invokePreReverseRelationship() = 0;

    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallPReversedRelationship() = 0;
    virtual std::shared_ptr<IReadEntityManager<std::string>> getReadProcedureManager() = 0;
    virtual std::shared_ptr<IReadRelationshipManager<std::string, std::string>> getCallPReadManager() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTRelationship() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getModifiesPRelationship() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getUsesPRelationship() = 0;
};
