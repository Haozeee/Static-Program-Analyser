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

template<template<typename, typename> typename Relationship_Read_Or_Write,
         template<typename> typename Entity_Read_Or_Write>
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
    Relationship_Read_Or_Write<int, int>* getFollowsManager() {
        return followsManager;
    }

    Relationship_Read_Or_Write<int, int>* getFollowsTManager() {
        return followsTManager;
    }

    Relationship_Read_Or_Write<int, int>* getParentManager() {
        return parentManager;
    }

    Relationship_Read_Or_Write<int, int>* getParentTManager() {
        return parentTManager;
    }

    Relationship_Read_Or_Write<std::string, std::string>* getUsesPManager() {
        return usesPManager;
    }

    Relationship_Read_Or_Write<int, std::string>* getUsesSManager() {
        return usesSManager;
    }

    Relationship_Read_Or_Write<std::string,
    std::string>* getModifiesPManager() {
        return modifiesPManager;
    }

    Relationship_Read_Or_Write<int, std::string>* getModifiesSManager() {
        return modifiesSManager;
    }

    Entity_Read_Or_Write<int>* getAssignManager() {
        return assignManager;
    }

    Entity_Read_Or_Write<int>* getCallManager() {
        return callManager;
    }

    Entity_Read_Or_Write<int>* getConstantManager() {
        return constantManager;
    }

    Entity_Read_Or_Write<int>* getIfManager() {
        return ifManager;
    }

    Entity_Read_Or_Write<int>* getPrintManager() {
        return printManager;
    }

    Entity_Read_Or_Write<std::string>* getProcedureManager() {
        return procedureManager;
    }

    Entity_Read_Or_Write<int>* getReadManager() {
        return readManager;
    }

    Entity_Read_Or_Write<int>* getStmtManager() {
        return stmtManager;
    }

    Entity_Read_Or_Write<std::string> getVariableManager() {
        return variableManager;
    }
};
