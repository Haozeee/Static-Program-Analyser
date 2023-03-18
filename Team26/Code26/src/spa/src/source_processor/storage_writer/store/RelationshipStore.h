#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "program_knowledge_base/StorageManager.h"

class RelationshipStore : public IRelationshipStore {
 private:
    std::shared_ptr<IWriteRelationshipManager<int, int>> followsManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> followsTManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> parentsManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> parentsTManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> usesSManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> modifiesSManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> usesPManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> modifiesPManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> nextManager;

    std::shared_ptr<IWriteRelationshipManager<int, std::string>> callSManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> callPManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> callsTManager;

    std::shared_ptr<ReadStorage> readStorage;

    // Calls, UsesP, UsesS, ModifiesP, ModifiesP Interlinking
//    std::shared_ptr<IReadRelationshipManager<std::string, std::string>> callPReadManager;
//    std::shared_ptr<IReadRelationshipManager<std::string, std::string>> usesPReadManager;
//    std::shared_ptr<IReadRelationshipManager<std::string, std::string>> modifiesPReadManager;
//    std::shared_ptr<IReadRelationshipManager<std::string, std::string>> callsTReadManager;

 public:
    explicit RelationshipStore(const std::shared_ptr<WriteStorage>& writeStorage,
                               const std::shared_ptr<ReadStorage>& readStorage);


    std::unordered_map<std::string, std::unordered_set<std::string>> getCallPReversedRelationship() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTRelationship() override;
    std::shared_ptr<IReadEntityManager<std::string>> getReadProcedureManager() override;
    std::shared_ptr<IReadRelationshipManager<std::string, std::string>> getCallPReadManager() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getModifiesPRelationship() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getUsesPRelationship() override;

    void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) override;
    void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) override;
    void insertFollowsTRelationship(const int &previousTStmtNo, const int &currentStmtNo) override;
    void insertParentsTRelationship(const int &parentTStmtNo, const int &childStmtNo) override;
    void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) override;
    void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) override;
    void insertUsesPRelationship(const std::string  &procedureName, const std::string &variableName) override;
    void insertModifiesPRelationship(const std::string  &procedureName, const std::string &variableName) override;
    void insertCallsRelationship(const int &stmtNo, const std::string &callerName,
                                 const std::string &calleeName) override;
    void insertCallsTRelationship(std::string caller, std::string callee) override;
    void insertNextRelationship(int previousStmtNo, int currStmtNo) override;

    void invokePostReverseRelationship() override;
    void invokePreReverseRelationship() override;
};
