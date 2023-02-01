#include "QueryManager.h"
#include "QueryTokenizer.h"
#include <iostream>
#include <memory>
#include <vector>
#include "QueryEvaluator.h"
#include "parser/QueryParser.h"
#include "parser/Query.h"


void QueryManager::process(const std::string& query) {
    // Tokenize QPS query
    QueryTokenizer tokenizer = QueryTokenizer(query);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();
    // For testing
    /**
    for (auto token : tokens) {
        std::cout << "value: " << token->getValue() << "\n";
    }
     */
    // Parse tokens with Parser

    // Validate Query

    // Evaluate query
}
