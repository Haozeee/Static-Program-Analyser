#pragma once
#include <string>
#include <list>
#include "../program_knowledge_base/StorageUtil.h"
#include "../program_knowledge_base/ReadOnlyStorage.h"

class ReadOnlyStorage;

class QueryManager {
 public:
    void process(const std::string& query, std::list<std::string> &results, std::shared_ptr<StorageUtil> storageUtil);
};
