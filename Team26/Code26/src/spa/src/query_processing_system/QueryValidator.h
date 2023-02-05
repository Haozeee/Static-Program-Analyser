#pragma once

#include "query_processing_system/parser/Query.h"

class QueryValidator {
 private:
    // Validation for Declarations
    // Structure: design-entity (',', synonym)*';'
    // Example: variable v; assign a; procedure p; constant c; stmt s;
    // Example: variable v1, v2, v3; assign a1, a2; procedure p, q;
    // Invalid example: variable, v, v, v; assign a, a; procedure p, p;
    /**
     * Validate that during Declaration, there are no duplicated Synonyms.
     *
     * @param query Query that is passed.
     */
    void validateNoDuplicateSynonymsInDeclaration(Query&);

    // Validation for Select Clauses
    // Structure: select-cl: declaration* 'Select' synonym
    // Example: variable v; Select v;
    // Invalid example: variable v;  Select v1;
    /**
     * Validate that the Synonym in the Select Clause was previously declared.
     *
     * @param query Query that is passed.
     */
    void validateSynonymInSelectClauseWasDeclared (Query&);


 public:
    QueryValidator();

    void validateQuery(Query&);
};
