#include "Query.h"
#include <algorithm>

Query::Query() {}

Query::~Query() {}

void Query::addDeclaration(Synonym synonym, DesignEntity designEntity) {
    declarations.push_back(std::make_shared<Declaration>(synonym, designEntity));
}

void Query::addSuchThatClause(std::shared_ptr<SuchThatClause> clause) {
    suchThatClauses.push_back(clause);
}

std::shared_ptr<SelectClause> Query::getSelectClause() {
    return selectClause;
}

std::vector<std::shared_ptr<Declaration>> Query::getDeclarations() {
    return declarations;
}

std::vector<std::shared_ptr<SuchThatClause>> Query::getSuchThatClauses() {
    return suchThatClauses;
}

// TODO(TBD): Implement
void Query::setSelectClause() {
}

bool Query::operator==(const Query &other) const {
    // Check if 2 pointers are equal by checking if the objects they are pointed to are equals
    auto ptrComparisonPredicate = [](const auto &item1, const auto &item2) {
        return (*item1) == (*item2);
    };

    bool sameDeclarations = std::is_permutation(declarations.begin(), declarations.end(),
                                                other.declarations.begin(), other.declarations.end(),
                                                ptrComparisonPredicate);
    // TODO(TBD): Implement
    bool sameSelectClause = 1;

    return sameDeclarations && sameSelectClause;
}
