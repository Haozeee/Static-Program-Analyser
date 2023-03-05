#pragma once

#include <string>
#include <memory>
#include "source_processor/storage_writer/interface/IPatternStore.h"
#include "program_knowledge_base/StorageManager.h"

class PatternStore : public IPatternStore {
 private:
    std::shared_ptr<IWritePatternManager> patternManager;
 public:
    explicit PatternStore(std::shared_ptr<WriteStorage> storage);

    void insertExpressionPattern(std::shared_ptr<AssignNode> node) override;
};