#pragma once

#include <string>
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesSManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesSManager.h"
#include "program_knowledge_base/entity/entity_child_managers/AssignManager.h"
#include "program_knowledge_base/entity/entity_child_managers/PrintManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ReadManager.h"
#include "program_knowledge_base/entity/entity_child_managers/StmtManager.h"
#include "program_knowledge_base/entity/entity_child_managers/VariableManager.h"
#include "program_knowledge_base/entity/entity_child_managers/IfManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ConstantManager.h"
#include "program_knowledge_base/entity/entity_child_managers/CallManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ProcedureManager.h"

template<template<typename, typename> typename RELATIONSHIP_READ_OR_WRITE, template<typename> typename ENTITY_READ_OR_WRITE>
class Storage {
 private:
    // relationship managers
    FollowsManager* followsManager = new FollowsManager();
    FollowsTManager* followsTManager = new FollowsTManager();
    ParentManager* parentManager = new ParentManager();
    ParentTManager* parentTManager = new ParentTManager();
    UsesPManager* usesPManager = new UsesPManager();
    UsesSManager* usesSManager = new UsesSManager();
    ModifiesPManager* modifiesPManager = new ModifiesPManager();
    ModifiesSManager* modifiesSManager = new ModifiesSManager();

    // entity managers
    AssignManager* assignManager = new AssignManager();
    CallManager* callManager = new CallManager();
    ConstantManager* constantManager = new ConstantManager();
    IfManager* ifManager = new IfManager();
    PrintManager* printManager = new PrintManager();
    ProcedureManager* procedureManager = new ProcedureManager();
    ReadManager* readManager = new ReadManager();
    StmtManager* stmtManager = new StmtManager();
    VariableManager* variableManager = new VariableManager();

 public:
    RELATIONSHIP_READ_OR_WRITE<int, int>* getFollowsManager() {
        return followsManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, int>* getFollowsTManager() {
        return followsTManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, int>* getParentManager() {
        return parentManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, int>* getParentTManager() {
        return parentTManager;
    }

    RELATIONSHIP_READ_OR_WRITE<std::string, std::string>* getUsesPManager() {
        return usesPManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, std::string>* getUsesSManager() {
        return usesSManager;
    }

    RELATIONSHIP_READ_OR_WRITE<std::string,
    std::string>* getModifiesPManager() {
        return modifiesPManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, std::string>* getModifiesSManager() {
        return modifiesSManager;
    }

    ENTITY_READ_OR_WRITE<int> getAssignManager() {
        return assignManager;
    }

    ENTITY_READ_OR_WRITE<int> getCallManager() {
        return callManager;
    }

    ENTITY_READ_OR_WRITE<int> getConstantManager() {
        return constantManager;
    }

    ENTITY_READ_OR_WRITE<int> getIfManager() {
        return ifManager;
    }

    ENTITY_READ_OR_WRITE<int> getPrintManager() {
        return printManager;
    }

    ENTITY_READ_OR_WRITE<std::string> getProcedureManager() {
        return procedureManager;
    }

    ENTITY_READ_OR_WRITE<int> getReadManager() {
        return readManager;
    }

    ENTITY_READ_OR_WRITE<int> getStmtManager() {
        return stmtManager;
    }

    ENTITY_READ_OR_WRITE<std::string> getVariableManager() {
        return variableManager;
    }
};
