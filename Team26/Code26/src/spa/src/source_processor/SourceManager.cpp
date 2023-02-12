#include "SourceManager.h"
#include <fstream>
#include <iostream>
#include <memory>
#include "source_processor/tokenizer/Tokenizer.h"
#include "source_processor/parser/Parser.h"
#include "program_knowledge_base/StorageUtil.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/DesignExtractor.h"

void SourceManager::process(std::string filename, std::shared_ptr<StorageUtil> storageUtil) {
    std::ifstream input(filename);

    if (!input) {
        // #TODO(zhengteck): Throw Error
    }

    Tokenizer sourceTokenizer = Tokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();

    Parser sourceParser = Parser(tokens);
    auto programNode = sourceParser.parse();

    std::shared_ptr<WriteOnlyStorage> writeStorage  = std::make_shared<WriteOnlyStorage>(storageUtil);
    std::shared_ptr<Store> store = std::make_shared<Store>(writeStorage);

    DesignExtractor designExtractor = DesignExtractor(store);
    designExtractor.extract(programNode);

    input.close();
}
