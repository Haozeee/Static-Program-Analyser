#pragma once

#include <memory>
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
    std::shared_ptr<FollowsManager> followsManager = std::make_shared<FollowsManager>();
    std::shared_ptr<FollowsTManager> followsTManager = std::make_shared<FollowsTManager>();
    std::shared_ptr<ParentManager> parentManager = std::make_shared<ParentManager>();
    std::shared_ptr<ParentTManager> parentTManager = std::make_shared<ParentTManager>();
    std::shared_ptr<UsesPManager> usesPManager = std::make_shared<UsesPManager>();
    std::shared_ptr<UsesSManager> usesSManager = std::make_shared<UsesSManager>();
    std::shared_ptr<ModifiesPManager> modifiesPManager = std::make_shared<ModifiesPManager>();
    std::shared_ptr<ModifiesSManager> modifiesSManager = std::make_shared<ModifiesSManager>();

    // entity managers
    std::shared_ptr<AssignManager> assignManager = std::make_shared<AssignManager>();
    std::shared_ptr<CallManager> callManager = std::make_shared<CallManager>();
    std::shared_ptr<ConstantManager> constantManager = std::make_shared<ConstantManager>();
    std::shared_ptr<IfManager> ifManager = std::make_shared<IfManager>();
    std::shared_ptr<PrintManager> printManager = std::make_shared<PrintManager>();
    std::shared_ptr<ProcedureManager> procedureManager = std::make_shared<ProcedureManager>();
    std::shared_ptr<ReadManager> readManager = std::make_shared<ReadManager>();
    std::shared_ptr<StmtManager> stmtManager = std::make_shared<StmtManager>();
    std::shared_ptr<VariableManager> variableManager = std::make_shared<VariableManager>();

 public:
    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getFollowsManager() {
        return followsManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getFollowsTManager() {
        return followsTManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getParentManager() {
        return parentManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getParentTManager() {
        return parentTManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getUsesPManager() {
        return usesPManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, std::string>> getUsesSManager() {
        return usesSManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getModifiesPManager() {
        return modifiesPManager;
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, std::string>> getModifiesSManager() {
        return modifiesSManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getAssignManager() {
        return assignManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getCallManager() {
        return callManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getConstantManager() {
        return constantManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getIfManager() {
        return ifManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getPrintManager() {
        return printManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getProcedureManager() {
        return procedureManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getReadManager() {
        return readManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getStmtManager() {
        return stmtManager;
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getVariableManager() {
        return variableManager;
    }
};
