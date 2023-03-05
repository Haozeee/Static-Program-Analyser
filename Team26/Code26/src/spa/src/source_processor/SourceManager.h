#pragma once

#include <string>
#include <memory>
#include "source_processor/storage_writer/interface/IStore.h"
#include "program_knowledge_base/StorageManager.h"

class SourceManager {
 public:
    void process(const std::string& filename, const std::shared_ptr<IStore>& store, const std::shared_ptr<ReadStorage>&
    readStorage);
};
