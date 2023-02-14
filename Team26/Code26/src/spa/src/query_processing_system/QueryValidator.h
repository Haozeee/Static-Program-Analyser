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

class QueryValidator {
 private:
    /**
     * Query wrapper object.
     */
    Query* query;

    /**
     * Validate that during Declaration, there are no duplicated Synonyms.
     * Validation for Declarations
     * Structure: design-entity (',', synonym)*';'
     * Example: variable v; assign a; procedure p; constant c; stmt s;
     * Example: variable v1, v2, v3; assign a1, a2; procedure p, q;
     * Invalid example: variable, v, v, v; assign a, a; procedure p, p;
     */
    void validateNoDuplicateSynonymsInDeclaration();

    /**
     * Validate that the Synonym in the Select Clause was previously declared.
     * Validation for Select Clauses
     * Structure: select-cl: declaration* 'Select' synonym
     * Example: variable v; Select v;
     * Invalid example: variable v;  Select v1;
     */
    void validateSynonymInSelectClauseWasDeclared();

    void validateSuchThatClause();

    /**
     * Follows & Parent (stmtRef, stmtRef)
     * Uses & Modifies (entRef, stmtRef)
     * stmtRef: Synonym, Wildcard, Number
     * entRef: Synonym, Wildcard, Character String
     */
    void validateArgumentTypeInSuchThatClause();

    /**
     * Synonyms of design entities can appear as relationship arguments,
     * and should match the design entity defined for the relationship.
     */
    void validateDesignEntityOfArgumentInSuchThatClause();

    std::unordered_set<std::string> getDeclarationSynonyms();

    bool containsSelectClauseSynonymInDeclaration(const std::unordered_set<std::string>&,
                                      const std::unordered_set<std::string>&);

 public:
    explicit QueryValidator(Query* query);

    void validateQuery();
};
