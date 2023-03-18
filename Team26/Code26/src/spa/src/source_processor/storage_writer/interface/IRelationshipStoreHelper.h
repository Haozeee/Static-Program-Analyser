#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "program_knowledge_base/entity/IReadEntityManager.h"
#include "program_knowledge_base/relationship/IReadRelationshipManager.h"

class IRelationshipStoreHelper {
 public:
    virtual void invokePostReverseRelationship() = 0;
    virtual void invokePreReverseRelationship() = 0;


    virtual std::unordered_set<std::string> getProcedureEntities() = 0;
    virtual bool isProcedureEntitiesContains(std::string procedureName) = 0;
    virtual bool callsPReadContains(std::string procedureName1, std::string procedureName2) = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallPReversedRelationship() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTRelationship() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getModifiesPRelationship() = 0;
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getUsesPRelationship() = 0;
};
