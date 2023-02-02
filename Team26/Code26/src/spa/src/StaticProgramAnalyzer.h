#pragma once
#include <string>
#include <list>
#include "source_processor/SourceManager.h"
#include "query_processing_system/QueryManager.h"

class StaticProgramAnalyzer {
 private:
    SourceManager sourceManager;
    QueryManager queryManager;

 public:
    void readProgramFromFile(std::string filename);
    void evaluateQuery(std::string query, std::list<std::string>& results);
};
