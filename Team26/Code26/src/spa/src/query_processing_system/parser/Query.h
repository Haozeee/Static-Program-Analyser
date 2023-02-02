#pragma once

#include <vector>
#include <memory>
#include "SelectClause.h"
#include "Declaration.h"
#include "Synonym.h"

class Query {
 private:
    // Select clause of the Query
    std::shared_ptr<SelectClause> selectClause;
    // List of declarations in the query
    std::vector<std::shared_ptr<Declaration>> declarations;

 public:
    Query();

    ~Query();

    std::shared_ptr<SelectClause> getSelectClause();

    std::vector<std::shared_ptr<Declaration>> getDeclarations();

    void setSelectClause();

    /**
     * Add a new declaration to the Query object.
     * @param synonym The synonym of the declaration.
     * @param designEntity The design entity of the synonym.
     */
    void addDeclaration(Synonym synonym, DesignEntity designEntity);

    bool operator==(const Query& other) const;
};
