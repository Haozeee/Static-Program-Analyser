#include "QueryValidator.h"

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

    if (!containsSelectClauseSynonymInDeclaration(declarationSynonyms, selectClauseSynonyms)) {
        throw QueryValidationException(QueryValidatorSynonymInSelectClauseNotDeclared + *selectClauseSynonyms.begin());
    }
}

bool QueryValidator::containsSelectClauseSynonymInDeclaration(
        const std::unordered_set<std::string> &declarationSynonyms,
        const std::unordered_set<std::string> &selectClauseSynonyms) {
    return std::all_of(selectClauseSynonyms.begin(), selectClauseSynonyms.end(),
                       [&declarationSynonyms](const std::string& elem) {
                           return declarationSynonyms.find(elem) != declarationSynonyms.end();
                       });
}

void QueryValidator::validateQuery(Query& query) {
    validateNoDuplicateSynonymsInDeclaration(query);

    validateSynonymInSelectClauseWasDeclared(query);
}