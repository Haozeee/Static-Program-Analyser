#pragma once

#include <memory>
#include <string>
#include "StorageUtil.h"
#include "program_knowledge_base/entity/entity_child_managers/AssignManager.h"
#include "program_knowledge_base/entity/entity_child_managers/PrintStmtNoManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ReadStmtNoManager.h"
#include "program_knowledge_base/entity/entity_child_managers/StmtManager.h"
#include "program_knowledge_base/entity/entity_child_managers/VariableManager.h"
#include "program_knowledge_base/entity/entity_child_managers/IfManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ConstantManager.h"
#include "program_knowledge_base/entity/entity_child_managers/CallManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ProcedureManager.h"
#include "program_knowledge_base/entity/entity_child_managers/WhileManager.h"
#include "program_knowledge_base/pattern/PatternManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesSManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesSManager.h"

template<template<typename, typename> typename Relationship_Read_Or_Write,
         template<typename> typename Entity_Read_Or_Write,
                 typename Pattern_Read_Or_Write>
class Storage {
 private:
    std::shared_ptr<StorageUtil> storage;

 public:
    explicit Storage(std::shared_ptr<StorageUtil> storageUtil) : storage(storageUtil) {}

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getFollowsManager() {
        return storage->getFollowsManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getFollowsTManager() {
        return storage->getFollowsTManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getParentManager() {
        return storage->getParentManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getParentTManager() {
        return storage->getParentTManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getUsesPManager() {
        return storage->getUsesPManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, std::string>> getUsesSManager() {
        return storage->getUsesSManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getModifiesPManager() {
        return storage->getModifiesPManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, std::string>> getModifiesSManager() {
        return storage->getModifiesSManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<int, int>> getNextManager() {
        return storage->getNextManager();
    }
    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getCallsManager() {
        return storage->getCallsManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getCallsPTManager() {
        return storage->getCallsPTManager();
    }

    std::shared_ptr<Relationship_Read_Or_Write<std::string, std::string>> getCallsPSManager() {
        return storage->getCallsPSManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getAssignManager() {
        return storage->getAssignManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getCallManager() {
        return storage->getCallManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getConstantManager() {
        return storage->getConstantManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getIfManager() {
        return storage->getIfManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getPrintStmtNoManager() {
        return storage->getPrintStmtNoManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getPrintVariableManager() {
        return storage->getPrintVariableManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getProcedureManager() {
        return storage->getProcedureManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getReadStmtNoManager() {
        return storage->getReadStmtNoManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getReadVariableManager() {
        return storage->getReadVariableManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getStmtManager() {
        return storage->getStmtManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<std::string>> getVariableManager() {
        return storage->getVariableManager();
    }

    std::shared_ptr<Entity_Read_Or_Write<int>> getWhileManager() {
        return storage->getWhileManager();
    }

    std::shared_ptr<Pattern_Read_Or_Write> getPatternManager() {
        return storage->getPatternManager();
    }
};
