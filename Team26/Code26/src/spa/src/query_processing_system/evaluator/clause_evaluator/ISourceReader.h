#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <utility>
#include "RelationResultType.h"
#include "program_knowledge_base/StorageManager.h"
#include "query_processing_system/parser/DesignEntity.h"

/**
 * An interface that is used to read contents from a given source code.
 * The data of the source code may be stored in different classes or different data structures,
 * thus this interface allows us to adhere to the dependency inversion principle.
 */
class ISourceReader {
 public:
    // Get entities of source programme
    virtual EntitySet getStringEntitiesFromPkb(DesignEntity entity) = 0;

    virtual StmtSet getIntEntitiesFromPkb(DesignEntity entity) = 0;

    virtual EntitySet getEntitiesFromPkb(DesignEntity entity) = 0;

    /**
     * The functions belows are used to obtain relationships values of the given source programme.
     * The interested values indicate the values in the map which we are interested in, hence
     * these values should be in the results, should they exist.
     */
    virtual StmtStmtMap getFollowsMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getFollowsTMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getParentMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getParentTMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getNextMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getNextTMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getAffectsMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getAffectsTMap(StmtSet &interestedValues) = 0;

    virtual StmtEntityMap getUsesSMap(StmtSet &interestedValues) = 0;

    virtual StmtEntityMap getModifiesSMap(StmtSet &interestedValues) = 0;

    virtual EntityEntityMap getUsesPMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getModifiesPMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getCallsMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getCallsTMap(EntitySet &interestedValues) = 0;

    virtual StmtEntityMap getCallsSMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getFollowsReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getFollowsTReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getParentReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getParentTReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getNextReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getNextTReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getAffectsReverseMap(StmtSet &interestedValues) = 0;

    virtual StmtStmtMap getAffectsTReverseMap(StmtSet &interestedValues) = 0;

    virtual EntityStmtMap getUsesSReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityStmtMap getModifiesSReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getUsesPReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getModifiesPReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getCallsReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityEntityMap getCallsTReverseMap(EntitySet &interestedValues) = 0;

    virtual EntityStmtMap getCallsSReverseMap(EntitySet &interestedValues) = 0;

    /**
     * Check if a given relationship in a source programme is empty
     */
    virtual bool isFollowsEmpty() = 0;

    virtual bool isParentEmpty() = 0;

    virtual bool isNextEmpty() = 0;

    virtual bool isAffectsEmpty() = 0;

    virtual bool isModifiesSEmpty() = 0;

    virtual bool isUsesSEmpty() = 0;

    virtual bool isModifiesPEmpty() = 0;

    virtual bool isUsesPEmpty() = 0;

    virtual bool isCallsEmpty() = 0;

    /**
     * Patterns
     */
     virtual StmtEntityMap getAllIfCondEntries() = 0;

     virtual EntityStmtMap getAllReverseIfCondEntries() = 0;

     virtual StmtEntityMap getAllWhileCondEntries() = 0;

     virtual EntityStmtMap getAllReverseWhileCondEntries() = 0;

     virtual AssignStatements getAssignStatementEntries(EntitySet &interestedEntries) = 0;
};
