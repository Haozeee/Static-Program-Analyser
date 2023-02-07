#include "StaticProgramAnalyzer.h"
#include <utility>

void StaticProgramAnalyzer::readProgramFromFile(std::string filename) {
    sourceManager.process(std::move(filename), storageUtil);
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string>& results) {
    queryManager.process(query, results, storageUtil);
}
