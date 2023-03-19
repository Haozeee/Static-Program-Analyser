#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "source_processor/storage_writer/Store.h"
#include "source_processor/design_extractor/interface/IExtractor.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "program_knowledge_base/StorageManager.h"

class DesignExtractor {
 private:
    std::unique_ptr<IExtractor> entityExtractor;
    std::unique_ptr<IExtractor> relationshipExtractor;

 public:
    explicit DesignExtractor(const std::shared_ptr<IStore>& store);
    void extract(const std::shared_ptr<ProgramNode>& programNode);
};
