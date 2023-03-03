#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "source_processor/storage_writer/Store.h"
#include "program_knowledge_base/StorageManager.h"
#include "source_processor/design_extractor/extractor/BaseExtractor.h"


class DesignExtractor {
 private:
    std::unique_ptr<BaseExtractor> entityExtractor;
    std::unique_ptr<BaseExtractor> relationshipExtractor;
    std::unique_ptr<BaseExtractor> patternExtractor;

 public:
    explicit DesignExtractor(const std::shared_ptr<IStore>& store);
    void extract(const std::shared_ptr<ProgramNode>& programNode);
};
