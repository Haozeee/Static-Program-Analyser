#include "StaticProgramAnalyzer.h"

void StaticProgramAnalyzer::readProgramFromFile(std::string filename) {
    sourceManager.process(std::move(filename));
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string> &results) {
    // queryManager
    queryManager.process(query);
    // storageManager
}
