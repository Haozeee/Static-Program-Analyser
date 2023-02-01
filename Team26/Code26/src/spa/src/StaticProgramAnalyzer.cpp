#include "StaticProgramAnalyzer.h"
#include "query_processing_system/QueryManager.h"

void StaticProgramAnalyzer::readProgramFromFile(std::string filename) {
    // sp to process file
}

void StaticProgramAnalyzer::evalauteQuery(std::string query, std::list<std::string> &results) {
    // queryManager
    QueryManager queryManager;
    queryManager.process(query);
    // storageManager
}
