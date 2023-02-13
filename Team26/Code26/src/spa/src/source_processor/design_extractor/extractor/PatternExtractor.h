#pragma once

#include <memory>
#include "source_processor/design_extractor/interface/IPatternExtractor.h"
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/storage/interface/IPatternStore.h"


class PatternExtractor : public BaseExtractor, public IPatternExtractor {
 private:
    std::shared_ptr<IPatternStore> patternStore;
 public:
    explicit PatternExtractor(std::shared_ptr<IPatternStore> storage);

    void extractStmt(std::shared_ptr<StmtNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
};
