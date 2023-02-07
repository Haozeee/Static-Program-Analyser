#pragma once
#include <string>
#include <list>
#include <memory>
#include "source_processor/SourceManager.h"
#include "query_processing_system/QueryManager.h"
#include "program_knowledge_base/StorageUtil.h"

class StaticProgramAnalyzer {
 private:
    QueryManager queryManager;
    SourceManager sourceManager;
    std::shared_ptr<StorageUtil> storageUtil =  std::make_shared<StorageUtil>();

 public:
    void readProgramFromFile(std::string filename);
    void evaluateQuery(std::string query, std::list<std::string>& results);
};
