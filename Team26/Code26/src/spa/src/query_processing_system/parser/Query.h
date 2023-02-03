#pragma once

#include <vector>
#include <memory>
#include "SelectClause.h"
#include "Declaration.h"
#include "Synonym.h"
#include "clause/suchThatClause/SuchThatClause.h"

class Query {
 private:
    // Select clause of the Query
    std::shared_ptr<SelectClause> selectClause;
    // List of declarations in the query
    std::vector<std::shared_ptr<Declaration>> declarations;
    // List of such that clauses in the query
    std::vector<std::shared_ptr<SuchThatClause>> suchThatClauses;

public:
    Query();

    ~Query();

    std::shared_ptr<SelectClause> getSelectClause();

    std::vector<std::shared_ptr<Declaration>> getDeclarations();

    std::vector<std::shared_ptr<SuchThatClause>> getSuchThatClauses();

    void setSelectClause();

    /**
     * Add a new declaration to the Query object.
     * @param synonym The synonym of the declaration.
     * @param designEntity The design entity of the synonym.
     */
    void addDeclaration(Synonym synonym, DesignEntity designEntity);

    /**
     * Add a new such that clause to the query.
     * @param clause The such that clause to be added.
     */
    void addSuchThatClause(std::shared_ptr<SuchThatClause> clause);

    bool operator==(const Query& other) const;
};
