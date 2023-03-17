#include "QueryManager.h"
#include <memory>
#include <vector>
#include "QueryTokenizer.h"
#include "QueryEvaluator.h"
#include "parser/QueryParser.h"
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "QueryValidator.h"

void QueryManager::process(const std::string& query, std::list<std::string> &results,
                           std::shared_ptr<ReadStorage> storageUtil) {
    // Create Query object
    auto * queryObject = new Query();
    try {
        // Tokenize QPS query
        QueryTokenizer tokenizer = QueryTokenizer(query);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        // Parse tokens with Parser
        QueryParser parser = QueryParser(tokens, queryObject);
        parser.parse();

        // Validate Query
        auto validator = QueryValidator(queryObject);
        validator.validateQuery();

        // Evaluate query
        QueryEvaluator evaluator = QueryEvaluator(queryObject, storageUtil);
        QueryDb queryDb = evaluator.evaluateQuery();
        auto queryResults = queryDb.getInterestedResults();

        // Add to qps result
        results.insert(results.end(), queryResults.begin(), queryResults.end());
    } catch (QuerySemanticException) {
        addSemanticError(results);
    } catch (QuerySyntaxException) {
        addSyntaxError(results);
    } catch (ParserException) {
        addSyntaxError(results);
    }

    // Memory management
    delete queryObject;
}

void QueryManager::addSyntaxError(std::list<std::string>& results) {
    results.clear();
    results.emplace_back("SyntaxError");
}

void QueryManager::addSemanticError(std::list<std::string>& results) {
    results.clear();
    results.emplace_back("SemanticError");
}
