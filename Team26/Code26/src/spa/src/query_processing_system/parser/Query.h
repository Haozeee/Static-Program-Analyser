#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <ostream>
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
    std::vector<SuchThatClause*> suchThatClauses;
    // Map of synonyms to design entity
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;

 public:
    Query();

    ~Query();

    DesignEntity getSynonymDesignEntity(std::shared_ptr<Synonym> synonym);

    std::shared_ptr<SelectClause> getSelectClause();

    std::vector<std::shared_ptr<Declaration>> getDeclarations();

    std::vector<SuchThatClause*> getSuchThatClauses();

    void setSelectClause(std::shared_ptr<SelectClause> selectClause);

    /**
     * Add a new declaration to the Query object.
     * @param synonym The synonym of the declaration.
     * @param designEntity The design entity of the synonym.
     */
    void addDeclaration(const Synonym& synonym, DesignEntity designEntity);

    /**
     * Add a new such that clause to the query.
     * @param clause The such that clause to be added.
     */
    void addSuchThatClause(SuchThatClause* clause);

    bool operator==(const Query& other) const;

    friend std::ostream& operator << (std::ostream& os, const Query& query);
};
