#pragma once
#include "query_processing_system/evaluator/clause_evaluator/ISourceReader.h"
#include <memory>

class MockStorageReader : public ISourceReader {
 private:
    StmtSet testStmtSet {1, 2, 3, 4, 5};

    EntitySet testEntitySet {"a", "b", "c", "d", "e"};

    StmtEntityMap testStmtEntityMap {
            {1, {"a", "b"}},
            {2, {"c"}},
            {3, {"a"}},
            {4, {}}
    };

    EntityStmtMap testEntityStmtMap {
            {"a", {1, 3}},
            {"b", {1}},
            {"c", {3}}
    };

    StmtStmtMap testStmtStmtMap {
            {1, {2, 3}},
            {4, {5}},
            {2, {3, 4, 5}},
            {5, {}}
    };

    StmtStmtMap testStmtStmtReverseMap {
            {2, {1}},
            {3, {1, 2}},
            {4, {2}},
            {5, {4, 2}}
    };

    EntityEntityMap testEntityEntityMap {
            {"a", {"b", "c"}},
            {"d", {"e"}},
            {"b", {"c", "d", "e"}},
            {"e", {}}
    };

    EntityEntityMap testEntityEntityReverseMap {
            {"b", {"a"}},
            {"c", {"a", "b"}},
            {"d", {"b"}},
            {"e", {"d", "b"}}
    };

 public:
    MockStorageReader();

    EntitySet getStringEntitiesFromPkb(DesignEntity entity) override;

    StmtSet getIntEntitiesFromPkb(DesignEntity entity) override;

    EntitySet getEntitiesFromPkb(DesignEntity entity) override;

    StmtStmtMap getFollowsMap(StmtSet &interestedValues) override;

    StmtStmtMap getFollowsTMap(StmtSet &interestedValues) override;

    StmtStmtMap getParentMap(StmtSet &interestedValues) override;

    StmtStmtMap getParentTMap(StmtSet &interestedValues) override;

    StmtStmtMap getNextMap(StmtSet &interestedValues) override;

    StmtStmtMap getNextTMap(StmtSet &interestedValues) override;

    StmtStmtMap getAffectsMap(StmtSet &interestedValues) override;

    StmtStmtMap getAffectsTMap(StmtSet &interestedValues) override;

    StmtEntityMap getUsesSMap(StmtSet &interestedValues) override;

    StmtEntityMap getModifiesSMap(StmtSet &interestedValues) override;

    EntityEntityMap getUsesPMap(EntitySet &interestedValues) override;

    EntityEntityMap getModifiesPMap(EntitySet &interestedValues) override;

    EntityEntityMap getCallsMap(EntitySet &interestedValues) override;

    EntityEntityMap getCallsTMap(EntitySet &interestedValues) override;

    StmtEntityMap getCallsSMap(EntitySet &interestedValues) override;

    StmtStmtMap getFollowsReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getFollowsTReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getParentReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getParentTReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getNextReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getNextTReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getAffectsReverseMap(StmtSet &interestedValues) override;

    StmtStmtMap getAffectsTReverseMap(StmtSet &interestedValues) override;

    EntityStmtMap getUsesSReverseMap(EntitySet &interestedValues) override;

    EntityStmtMap getModifiesSReverseMap(EntitySet &interestedValues) override;

    EntityEntityMap getUsesPReverseMap(EntitySet &interestedValues) override;

    EntityEntityMap getModifiesPReverseMap(EntitySet &interestedValues) override;

    EntityEntityMap getCallsReverseMap(EntitySet &interestedValues) override;

    EntityEntityMap getCallsTReverseMap(EntitySet &interestedValues) override;

    EntityStmtMap getCallsSReverseMap(EntitySet &interestedValues) override;

    bool isFollowsEmpty() override;

    bool isParentEmpty() override;

    bool isNextEmpty() override;

    bool isAffectsEmpty() override;

    bool isModifiesSEmpty() override;

    bool isUsesSEmpty() override;

    bool isModifiesPEmpty() override;

    bool isUsesPEmpty() override;

    bool isCallsEmpty() override;

    StmtEntityMap getAllIfCondEntries() override;

    EntityStmtMap getAllReverseIfCondEntries() override;

    StmtEntityMap getAllWhileCondEntries() override;

    EntityStmtMap getAllReverseWhileCondEntries() override;

    AssignStatements getAssignStatementEntries(EntitySet &interestedEntries) override;
};
