#include "StaticProgramAnalyzer.h"
#include <utility>

void StaticProgramAnalyzer::readProgramFromFile(std::string filename) {
    SourceManager::process(std::move(filename), storageUtil);
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string>& results) {
    // queryManager
    queryManager.process(query, results, storageUtil);
    // storageManager
}
