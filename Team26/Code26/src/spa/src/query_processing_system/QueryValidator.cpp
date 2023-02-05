#include "QueryValidator.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

QueryValidator::QueryValidator() = default;

void QueryValidator::validateNoDuplicateSynonymsInDeclaration(Query& query) {
    std::unordered_set<std::string> declaration;
    for (const auto &d : query.getDeclarations()) {
        std::string synonym = d->getSynonym().ident;
        if (declaration.find(synonym) != declaration.end()) {
            throw QueryValidationException(QueryValidatorDuplicatedSynonymInDeclaration + synonym);
        }
        declaration.insert(synonym);
    }
}

void QueryValidator::validateSynonymInSelectClauseWasDeclared(Query& query) {
    std::vector<std::shared_ptr<Declaration>> declarations;
    declarations = query.getDeclarations();
    std::unordered_set<std::string> declarationSynonyms;
    for (auto it = declarations.begin(); it != declarations.end(); ++it) {
        auto declaration = *it;
        std::string declarationSynonym = declaration->getSynonym().ident;
        declarationSynonyms.insert(declarationSynonym);
    }

    auto selectClauseItems = query.getSelectClause()->getSelectClauseItems();
    std::unordered_set<std::string> selectClauseSynonyms;
    for (auto item : *selectClauseItems) {
        std::string selectClauseSynonym = SelectClause::getSynonym(item);
        selectClauseSynonyms.insert(selectClauseSynonym);
    }

    std::unordered_set<std::string> result;
    std::set_difference(selectClauseSynonyms.begin(), selectClauseSynonyms.end(),
                        declarationSynonyms.begin(), declarationSynonyms.end(), std::inserter(result, result.begin()));

    if (result.size() > 0) {
        throw QueryValidationException(QueryValidatorSynonymInSelectClauseNotDeclared + *result.begin());
    }
}

void QueryValidator::validateQuery(Query& query) {
    validateNoDuplicateSynonymsInDeclaration(query);

    validateSynonymInSelectClauseWasDeclared(query);
}
