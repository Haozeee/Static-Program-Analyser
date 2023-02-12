#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "query_processing_system/parser/Query.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"

class QueryValidator {
 private:
    /**
     * Query wrapper object.
     */
    Query* query;

    // Validation for Declarations
    // Structure: design-entity (',', synonym)*';'
    // Example: variable v; assign a; procedure p; constant c; stmt s;
    // Example: variable v1, v2, v3; assign a1, a2; procedure p, q;
    // Invalid example: variable, v, v, v; assign a, a; procedure p, p;
    /**
     * Validate that during Declaration, there are no duplicated Synonyms.
     */
    void validateNoDuplicateSynonymsInDeclaration();

    // Validation for Select Clauses
    // Structure: select-cl: declaration* 'Select' synonym
    // Example: variable v; Select v;
    // Invalid example: variable v;  Select v1;
    /**
     * Validate that the Synonym in the Select Clause was previously declared.
     */
    void validateSynonymInSelectClauseWasDeclared();

    std::unordered_set<std::string> getDeclarationSynonyms();

    bool containsSelectClauseSynonymInDeclaration(const std::unordered_set<std::string>& declarationSynonyms,
                                      const std::unordered_set<std::string>& selectClauseSynonyms);

    void validateAssignPatternSynonym();

 public:
    explicit QueryValidator(Query* query);

    void validateQuery();
};
