#pragma once

#include <memory>
#include <string>
#include "source_processor/storage/interface/IRelationshipStore.h"
#include "program_knowledge_base/WriteOnlyStorage.h"

class RelationshipStore : public IRelationshipStore {
 private:
    std::shared_ptr<WriteOnlyRelationshipManger<int, int>> followsManager;
    std::shared_ptr<WriteOnlyRelationshipManger<int, int>> followsTManager;
    std::shared_ptr<WriteOnlyRelationshipManger<int, int>> parentManager;
    std::shared_ptr<WriteOnlyRelationshipManger<int, int>> parentTManager;
    std::shared_ptr<WriteOnlyRelationshipManger<int, std::string>> usesSManager;
    std::shared_ptr<WriteOnlyRelationshipManger<int, std::string>> modifiesSManager;
    std::shared_ptr<WriteOnlyRelationshipManger<std::string, std::string>> usesPManager;
    std::shared_ptr<WriteOnlyRelationshipManger<std::string, std::string>> modifiesPManager;

 public:
    explicit RelationshipStore(std::shared_ptr<WriteOnlyStorage> storage);

    void insertFollowsRelationship(int &previousStmtNo, int &currentStmtNo) override;
    void insertParentsRelationship(int &parentStmtNo, int &childStmtNo) override;
    void insertUsesSRelationship(int &stmtNo, std::string &variableName) override;
    void insertModifiesSRelationship(int &stmtNo, std::string &variableName) override;
    void insertUsesPRelationship(std::string  &procedureName, std::string &variableName) override;
    void insertModifiesPRelationship(std::string  &procedureName, std::string &variableName) override;
};
