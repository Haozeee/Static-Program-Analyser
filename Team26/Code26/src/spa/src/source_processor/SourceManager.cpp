#include "SourceManager.h"
#include <fstream>
#include <iostream>
#include "SourceTokenizer.h"

void SourceManager::process(std::string filename) {
    std::ifstream input(filename);

    if (!input) {
        // #TODO(zhengteck): Throw Error
    }

    SourceTokenizer sourceTokenizer = SourceTokenizer(&input);
    auto tokens = sourceTokenizer.tokenize();
    input.close();

    // TODO(future): Add Parsing, Design Extractor, Storage
}
