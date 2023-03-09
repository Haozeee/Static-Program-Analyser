#pragma once

#include <memory>
#include <string>
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "program_knowledge_base/StorageManager.h"

class RelationshipStore : public IRelationshipStore {
 private:
    std::shared_ptr<IWriteRelationshipManager<int, int>> followsManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> followsTManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> parentManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> parentTManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> usesSManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> modifiesSManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> usesPManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> modifiesPManager;
    std::shared_ptr<IWriteRelationshipManager<int, int>> nextManager;

    std::shared_ptr<IWriteRelationshipManager<int, std::string>> callSManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> callPManager;
    std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> callsTManager;

 public:
    explicit RelationshipStore(std::shared_ptr<WriteStorage> storage);

    void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) override;
    void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) override;
    void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) override;
    void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) override;
    void insertUsesPRelationship(const std::string  &procedureName, const std::string &variableName) override;
    void insertModifiesPRelationship(const std::string  &procedureName, const std::string &variableName) override;
    void insertCallsRelationship(const int &stmtNo, const std::string &callerName,
                                 const std::string &calleeName) override;
    void insertCallsTRelationship(std::string caller, std::string callee) override;
    void insertNextRelationship(int previousStmtNo, int currStmtNo) override;

    void invokeReverseRelationship() override;
};
