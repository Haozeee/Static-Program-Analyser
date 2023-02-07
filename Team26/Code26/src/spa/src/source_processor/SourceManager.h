#pragma once

#include <string>
#include "../program_knowledge_base/StorageUtil.h"

class SourceManager {
 public:
    void process(std::string filename, std::shared_ptr<StorageUtil> storageUtil);
};
