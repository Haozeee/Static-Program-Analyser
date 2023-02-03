#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <ostream>
#include "SelectClause.h"
#include "Declaration.h"
#include "Synonym.h"

class Query {
 private:
    // Select clause of the Query
    std::shared_ptr<SelectClause> selectClause;
    // List of declarations in the query
    std::vector<std::shared_ptr<Declaration>> declarations;
    // Map of synonyms to design entity
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;

 public:
    Query();

    ~Query();

    std::shared_ptr<SelectClause> getSelectClause();

    std::vector<std::shared_ptr<Declaration>> getDeclarations();

    DesignEntity getSynonymDesignEntity(const Synonym& synonym);

    void setSelectClause();

    /**
     * Add a new declaration to the Query object.
     * @param synonym The synonym of the declaration.
     * @param designEntity The design entity of the synonym.
     */
    void addDeclaration(const Synonym& synonym, DesignEntity designEntity);

    bool operator==(const Query& other) const;
};
