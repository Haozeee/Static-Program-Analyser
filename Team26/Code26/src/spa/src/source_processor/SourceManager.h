#pragma once

#include <string>
#include "../program_knowledge_base/StorageUtil.h"

class SourceManager {
 public:
    static void process(std::string filename, StorageUtil* storageUtil);
};
