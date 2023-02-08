#pragma once

#include "IPatternStore.h"
#include <memory>
#include <string>
#include "program_knowledge_base/WriteOnlyStorage.h"

class PatternStore : public IPatternStore {
 private:
    std::shared_ptr<WriteOnlyStorage> patternStorage;
 public:
    explicit PatternStore(std::shared_ptr<WriteOnlyStorage> storage);

    void insertExpressionPattern(std::string &expr) override;
};
