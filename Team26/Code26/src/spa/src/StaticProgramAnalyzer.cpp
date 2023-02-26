#include "StaticProgramAnalyzer.h"
#include <utility>

void StaticProgramAnalyzer::readProgramFromFile(const std::string& filename) {
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage());
    auto x = storageManager->getReadStorage();
    sourceManager.process(filename, store, storageManager->getReadStorage());
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string>& results) {
    queryManager.process(query, results, storageManager->getReadStorage());
}
