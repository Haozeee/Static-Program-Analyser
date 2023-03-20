#include "SourceManager.h"
#include <fstream>
#include <memory>
#include <utility>
#include "source_processor/tokenizer/SourceTokenizer.h"
#include "source_processor/parser/SourceParser.h"
#include "source_processor/design_extractor/DesignExtractor.h"

void SourceManager::process(const std::string& filename, const std::shared_ptr<IStore>& store) {
    std::ifstream input(filename);

    if (!input) {
        throw SourceManagerException(ManagerInvalidInputFile);
    }

    SourceTokenizer sourceTokenizer = SourceTokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();

    SourceParser sourceParser = SourceParser(tokens);
    sourceParser.parse();
    std::shared_ptr<ProgramNode> programRoot = sourceParser.getProgramNode();

    DesignExtractor designExtractor = DesignExtractor(store);
    designExtractor.extract(programRoot);

    input.close();
}
