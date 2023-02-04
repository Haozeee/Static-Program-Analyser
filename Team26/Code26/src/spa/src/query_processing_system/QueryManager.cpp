#include "QueryManager.h"
#include <iostream>
#include <memory>
#include <vector>
#include "QueryTokenizer.h"
#include "QueryEvaluator.h"
#include "parser/QueryParser.h"
#include "parser/Query.h"
#include "../program_knowledge_base/ReadOnlyStorage.h"

void QueryManager::process(const std::string& query) {
    // Create Query object
    auto * queryObject = new Query();
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
    QueryParser parser = QueryParser(tokens, queryObject);

    // Validate Query

    // Evaluate query
    std::shared_ptr<ReadOnlyStorage> storage = std::make_shared<ReadOnlyStorage>();
    //QueryEvaluator evaluator = QueryEvaluator(queryObject, storage);
    //evaluator.evaluateQuery();

    // Memory management
    // Delete created query object
    delete queryObject;
}
