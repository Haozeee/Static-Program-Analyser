#pragma once

#include <memory>
#include <string>
#include <utility>
#include "StorageUtil.h"

template<template<typename, typename> typename RelationshipReadOrWrite,
         template<typename> typename EntityReadOrWrite,
         template<typename, typename> typename PatternReadOrWrite>
class Storage {
 private:
    std::shared_ptr<StorageUtil> storage;

 public:
    explicit Storage(std::shared_ptr<StorageUtil> storageUtil) : storage(std::move(storageUtil)) {}

    std::shared_ptr<RelationshipReadOrWrite<int, int>> getFollowsManager() {
        return storage->getFollowsManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, int>> getFollowsTManager() {
        return storage->getFollowsTManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, int>> getParentManager() {
        return storage->getParentManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, int>> getParentTManager() {
        return storage->getParentTManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<std::string, std::string>> getUsesPManager() {
        return storage->getUsesPManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, std::string>> getUsesSManager() {
        return storage->getUsesSManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<std::string, std::string>> getModifiesPManager() {
        return storage->getModifiesPManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, std::string>> getModifiesSManager() {
        return storage->getModifiesSManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, int>> getNextManager() {
        return storage->getNextManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<std::string, std::string>> getCallsPManager() {
        return storage->getCallsPManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, std::string>> getCallsSManager() {
        return storage->getCallsSManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<std::string, std::string>> getCallsTManager() {
        return storage->getCallsTManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, std::string>> getIfCondManager() {
        return storage->getIfCondManager();
    }

    std::shared_ptr<RelationshipReadOrWrite<int, std::string>> getWhileCondManager() {
        return storage->getWhileCondManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getAssignManager() {
        return storage->getAssignManager();
    }

    std::shared_ptr<EntityReadOrWrite<std::string>> getCallProcedureManager() {
        return storage->getCallProcedureManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getCallStmtNoManager() {
        return storage->getCallStmtNoManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getConstantManager() {
        return storage->getConstantManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getIfManager() {
        return storage->getIfManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getPrintStmtNoManager() {
        return storage->getPrintStmtNoManager();
    }

    std::shared_ptr<EntityReadOrWrite<std::string>> getPrintVariableManager() {
        return storage->getPrintVariableManager();
    }

    std::shared_ptr<EntityReadOrWrite<std::string>> getProcedureManager() {
        return storage->getProcedureManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getReadStmtNoManager() {
        return storage->getReadStmtNoManager();
    }

    std::shared_ptr<EntityReadOrWrite<std::string>> getReadVariableManager() {
        return storage->getReadVariableManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getStmtManager() {
        return storage->getStmtManager();
    }

    std::shared_ptr<EntityReadOrWrite<std::string>> getVariableManager() {
        return storage->getVariableManager();
    }

    std::shared_ptr<EntityReadOrWrite<int>> getWhileManager() {
        return storage->getWhileManager();
    }

    std::shared_ptr<PatternReadOrWrite<std::string, std::shared_ptr<ShuntNode>>> getAssignPatternManager() {
        return storage->getAssignPatternManager();
    }
};
