#include "StaticProgramAnalyzer.h"
#include <utility>
#include <iostream>

void StaticProgramAnalyzer::readProgramFromFile(std::string filename) {
    sourceManager.process(std::move(filename));
}

void StaticProgramAnalyzer::evalauteQuery(std::string query, std::list<std::string> &results) {
    // queryManager
    // storageManager
}
