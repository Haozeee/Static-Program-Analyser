#include "SourceManager.h"
#include <fstream>
#include <memory>
#include <utility>
#include "source_processor/tokenizer/Tokenizer.h"
#include "source_processor/parser/Parser.h"
#include "source_processor/design_extractor/DesignExtractor.h"

void SourceManager::process(const std::string& filename, const std::shared_ptr<IStore>& store,
                            const std::shared_ptr<ReadStorage>&readStorage) {
    std::ifstream input(filename);

    if (!input) {
        throw SourceManagerException(ManagerInvalidInputFile);
    }

    Tokenizer sourceTokenizer = Tokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();

    Parser sourceParser = Parser(tokens);
    sourceParser.parse();
    std::shared_ptr<ProgramNode> programRoot = sourceParser.getProgramNode();

    DesignExtractor designExtractor = DesignExtractor(store, readStorage);
    designExtractor.extract(programRoot);

    input.close();
}
