#pragma once
#include <string>
#include <list>
#include "source_processor/SourceManager.h"

class StaticProgramAnalyzer {
 private:
    SourceManager sourceManager;
    QueryManager queryManager;

 public:
    void readProgramFromFile(std::string filename);
    void evalauteQuery(std::string query, std::list<std::string>& results);
};
