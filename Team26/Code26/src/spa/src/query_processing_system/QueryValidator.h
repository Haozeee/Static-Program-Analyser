#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "query_processing_system/parser/Query.h"
#include "query_processing_system/parser/clause/such_that_clause/SuchThatClauseValidationResult.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/ClauseArgumentsType.h"

class QueryValidator {
 private:
    /**
     * Query wrapper object.
     */
    Query* query;

    void validateDuplicateDeclarations();

    /**
     * Validate that the Synonym in the Select Clause was previously declared.
     * Validation for Select Clauses
     * Structure: select-cl: declaration* 'Select' synonym
     * Example: variable v; Select v;
     * Invalid example: variable v;  Select v1;
     */
    void validateSynonymInSelectClauseWasDeclared();

    void validateSuchThatClause();

    void validatePatternClause();

    void validateWithClause();

    std::unordered_set<std::string> getDeclarationSynonyms();

    bool containsSelectClauseSynonymInDeclaration(const std::unordered_set<std::string>&,
                                      const std::unordered_set<std::string>&);

 public:
    explicit QueryValidator(Query* query);

    void validateQuery();
};
