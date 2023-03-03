#pragma once

#include <string>
#include <memory>
#include "source_processor/storage_writer/interface/IStore.h"

class SourceManager {
 public:
    void process(const std::string& filename, std::shared_ptr<IStore> store);
};
