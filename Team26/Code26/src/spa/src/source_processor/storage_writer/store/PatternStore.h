#pragma once

#include <string>
#include <memory>
#include "source_processor/storage_writer/interface/IPatternStore.h"
#include "program_knowledge_base/StorageManager.h"

class PatternStore : public IPatternStore {
 private:
    std::shared_ptr<IWritePatternManager<std::string, std::shared_ptr<ShuntNode>>> patternManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> whileCondManager;
    std::shared_ptr<IWriteRelationshipManager<int, std::string>> ifCondManager;

 public:
    explicit PatternStore(const std::shared_ptr<WriteStorage>& storage);

    void insertExpressionPattern(std::shared_ptr<AssignNode> node) override;
    void insertCondExpressionIfStatement(int stmtIndex, std::string variableName) override;
    void insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) override;

    void invokePostReverseRelationship() override;
};
