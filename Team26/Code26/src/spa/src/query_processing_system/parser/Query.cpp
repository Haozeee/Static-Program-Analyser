#include "Query.h"

Query::Query() {}

Query::~Query() {}

std::shared_ptr<SelectClause> Query::getSelectClause() {
    return selectClause;
}

std::vector<std::shared_ptr<Declaration>> Query::getDeclarations() {
    return declarations;
}

void Query::addDeclaration(Synonym synonym, DesignEntity designEntity) {
    auto declaration = std::make_shared<Declaration>(synonym, designEntity);
    declarations.push_back(declaration);
}

// TODO
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
    // TODO
    bool sameSelectClause = 1;

    return sameDeclarations && sameSelectClause;
}
