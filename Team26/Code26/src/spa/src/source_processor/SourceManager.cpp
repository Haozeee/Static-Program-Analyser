#include "SourceManager.h"
#include <fstream>
#include <iostream>
#include "SourceTokenizer.h"
#include "SourceParser.h"
#include "program_knowledge_base/StorageSingleton.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/DesignExtractor.h"

void SourceManager::process(std::string filename) {
    std::ifstream input(filename);

    if (!input) {
        // #TODO(zhengteck): Throw Error
    }

    SourceTokenizer sourceTokenizer = SourceTokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();

    SourceParser sourceParser = SourceParser(tokens);
    auto programNode = sourceParser.parse();

    StorageSingleton* storage = StorageSingleton::getStorage();
    std::shared_ptr<WriteOnlyStorage> writeStorage  = std::make_shared<WriteOnlyStorage>(storage);
    DesignExtractor designExtractor = DesignExtractor(writeStorage);
    designExtractor.extract(programNode);

    input.close();
}
