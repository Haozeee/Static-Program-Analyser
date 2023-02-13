#include "SourceManager.h"
#include <fstream>
#include <memory>
#include <utility>
#include "source_processor/tokenizer/Tokenizer.h"
#include "source_processor/parser/Parser.h"
#include "source_processor/design_extractor/DesignExtractor.h"

void SourceManager::process(const std::string& filename, std::shared_ptr<IStore> store) {
    std::ifstream input(filename);

    if (!input) {
        // #TODO(zhengteck): Throw Error
    }

    Tokenizer sourceTokenizer = Tokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();

    Parser sourceParser = Parser(tokens);
    auto programNode = sourceParser.parse();

    DesignExtractor designExtractor = DesignExtractor(std::move(store));
    designExtractor.extract(programNode);

    input.close();
}
