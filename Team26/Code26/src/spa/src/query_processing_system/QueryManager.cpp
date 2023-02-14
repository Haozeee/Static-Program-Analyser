#include "QueryManager.h"
#include <iostream>
#include <memory>
#include <vector>
#include "QueryTokenizer.h"
#include "QueryEvaluator.h"
#include "parser/QueryParser.h"
#include "parser/Query.h"
#include "evaluator/QueryDb.h"

void QueryManager::process(const std::string& query, std::list<std::string> &results,
                           std::shared_ptr<ReadStroage> storageUtil) {
    // Create Query object
    auto * queryObject = new Query();
    // Tokenize QPS query
    QueryTokenizer tokenizer = QueryTokenizer(query);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

    // For testing (Print tokens)
    /**
    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        std::cout << "value: " << token->getValue() << "\n";
    }
    */

    // Parse tokens with Parser
    QueryParser parser = QueryParser(tokens, queryObject);
    parser.parse();
    // Validate Query
    // std::cout << *queryObject << "\n";

    // Create pkb read instance
//    auto storage = std::make_shared<ReadOnlyStorage>(storageUtil);

    // Evaluate query
    QueryEvaluator evaluator = QueryEvaluator(queryObject, storageUtil);
    QueryDb queryDb = evaluator.evaluateQuery();
    auto queryResults = queryDb.getInterestedResults();

    // Add to qps result
    for (auto const& item : queryResults) {
        for (auto str : item.second) {
            results.push_back(str);
        }
    }
    // Memory management
    delete queryObject;
}


