#include "StaticProgramAnalyzer.h"
#include <utility>

void StaticProgramAnalyzer::readProgramFromFile(const std::string& filename) {
//    std::shared_ptr<WriteOnlyStorage> writeStorage  = std::make_shared<WriteOnlyStorage>(storageUtil);
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteManager());
    sourceManager.process(filename, store);
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string>& results) {
    queryManager.process(query, results, storageManager->getReadManager());
}
