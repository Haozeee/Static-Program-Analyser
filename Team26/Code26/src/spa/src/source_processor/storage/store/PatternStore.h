#pragma once

#include <memory>
#include <string>
#include "source_processor/storage/interface/IPatternStore.h"
#include "program_knowledge_base/WriteOnlyStorage.h"

class PatternStore : public IPatternStore {
 private:
    std::shared_ptr<WriteOnlyStorage> patternStorage;
 public:
    explicit PatternStore(std::shared_ptr<WriteOnlyStorage> storage);

    void insertExpressionPattern(std::shared_ptr<AssignNode> node) override;
};
