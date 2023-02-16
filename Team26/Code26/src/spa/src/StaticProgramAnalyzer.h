#pragma once
#include <string>
#include <list>
#include <memory>
#include "source_processor/SourceManager.h"
#include "query_processing_system/QueryManager.h"
#include "source_processor/storage/Store.h"
#include "program_knowledge_base/StorageManager.h"

class StaticProgramAnalyzer {
 private:
    QueryManager queryManager;
    SourceManager sourceManager;
    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();

 public:
    void readProgramFromFile(const std::string& filename);
    void evaluateQuery(std::string query, std::list<std::string>& results);
};
