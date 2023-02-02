#pragma once

#include <string>
#include "relationship/FollowsManager.h"
#include "relationship/FollowsTManager.h"
#include "relationship/ParentManager.h"
#include "relationship/ParentTManager.h"
#include "relationship/UsesPManager.h"
#include "relationship/UsesSManager.h"
#include "relationship/ModifiesPManager.h"
#include "relationship/ModifiesSManager.h"

template<template<typename, typename> typename RELATIONSHIP_READ_OR_WRITE>
class StorageFacade {
 private:
    FollowsManager* followsManager = new FollowsManager();
    FollowsTManager* followsTManager = new FollowsTManager();
    ParentManager* parentManager = new ParentManager();
    ParentTManager* parentTManager = new ParentTManager();
    UsesPManager* usesPManager = new UsesPManager();
    UsesSManager* usesSManager = new UsesSManager();
    ModifiesPManager* modifiesPManager = new ModifiesPManager();
    ModifiesSManager* modifiesSManager = new ModifiesSManager();

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

    RELATIONSHIP_READ_OR_WRITE<std::string, std::string>* getModifiesPManager() {
        return modifiesPManager;
    }

    RELATIONSHIP_READ_OR_WRITE<int, std::string>* getModifiesSManager() {
        return modifiesSManager;
    }
};
