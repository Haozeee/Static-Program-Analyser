#include "QueryValidator.h"

QueryValidator::QueryValidator(Query* query) : query(query) {}

void QueryValidator::validateNoDuplicateSynonymsInDeclaration() {
    std::unordered_set<std::string> declaration;
    for (const auto &d : query->getDeclarations()) {
        std::string synonym = d->getSynonym().ident;
        if (declaration.find(synonym) != declaration.end()) {
            throw QueryValidationException(QueryValidatorDuplicatedSynonymInDeclaration + synonym);
        }
        declaration.insert(synonym);
    }
}

void QueryValidator::validateSynonymInSelectClauseWasDeclared() {
    std::unordered_set<std::string> declarationSynonyms = getDeclarationSynonyms();

    auto selectClauseItems = query->getSelectClause()->getSelectClauseItems();
    std::unordered_set<std::string> selectClauseSynonyms;
    for (auto item : *selectClauseItems) {
        std::string selectClauseSynonym = SelectClause::getSynonym(item);
        if (selectClauseSynonym == "BOOLEAN") return;
        selectClauseSynonyms.insert(selectClauseSynonym);
    }

    if (!containsSelectClauseSynonymInDeclaration(declarationSynonyms, selectClauseSynonyms)) {
        throw QueryValidationException(QueryValidatorUndeclaredSelectClauseSynonym + *selectClauseSynonyms.begin());
    }
}

std::unordered_set<std::string> QueryValidator::getDeclarationSynonyms() {
    std::vector<std::shared_ptr<Declaration>> declarations;
    declarations = query->getDeclarations();
    std::unordered_set<std::string> declarationSynonyms;
    for (auto it = declarations.begin(); it != declarations.end(); ++it) {
        auto declaration = *it;
        std::string declarationSynonym = declaration->getSynonym().ident;
        declarationSynonyms.insert(declarationSynonym);
    }
    return declarationSynonyms;
}

bool QueryValidator::containsSelectClauseSynonymInDeclaration(
        const std::unordered_set<std::string> &declarationSynonyms,
        const std::unordered_set<std::string> &selectClauseSynonyms) {
    return std::all_of(selectClauseSynonyms.begin(), selectClauseSynonyms.end(),
                       [&declarationSynonyms](const std::string& elem) {
                           return declarationSynonyms.find(elem) != declarationSynonyms.end();
                       });
}

void QueryValidator::validateSuchThatClause() {
    for (auto clause : query->getSuchThatClauses()) {
        auto validationResult = clause->isValidClause();
        auto leftArg = clause->getLeftArg();
        auto rightArg = clause->getRightArg();
        switch (validationResult) {
            case SuchThatClauseValidationResult::INVALID_LEFT_ARG_TYPE:
                throw QueryInvalidArgumentType(leftArg.getValue()
                                               + QueryValidatorInvalidFirstArgumentTypeInRelation);
            case SuchThatClauseValidationResult::INVALID_RIGHT_ARG_TYPE:
                throw QueryInvalidArgumentType(rightArg.getValue()
                                               + QueryValidatorInvalidSecondArgumentTypeInRelation);
            case SuchThatClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY:
                throw QueryValidationException("The synonym "
                                               + leftArg.getValue()
                                               + " of design entity "
                                               + toString(leftArg.getDesignEntity())
                                               + QueryValidatorInvalidFirstDesignEntityInRelation);
            case SuchThatClauseValidationResult::INVALID_RIGHT_DESIGN_ENTITY:
                throw QueryValidationException("The synonym "
                                               + rightArg.getValue()
                                               + " of design entity "
                                               + toString(rightArg.getDesignEntity())
                                               + QueryValidatorInvalidSecondDesignEntityInRelation);
            default:
                continue;
        }
    }
}

void QueryValidator::validatePatternClause() {
    for (auto clause : query->getPatternClause()) {
        auto validationResult = clause->isValidClause();
        auto patternArg = clause->getPatternArg();
        auto leftArg = clause->getLeftArg();
        auto rightArg = clause->getRightArg();
        if (patternArg.getDesignEntity() == DesignEntity::IF || patternArg.getDesignEntity() == DesignEntity::WHILE) {
            if (!rightArg.isWildCard()) {
                throw QueryValidationException(rightArg.getExpression()
                                                    + QueryValidatorIfWhilePatternRightArgWildcard);
            }
        }
        switch (validationResult) {
            case PatternClauseValidationResult::INVALID_LEFT_ARG_TYPE:
                throw QueryInvalidArgumentType(leftArg.getValue()
                                               + QueryValidatorInvalidFirstArgumentTypeInRelation);
            case PatternClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY:
                throw QueryValidationException("The synonym "
                                               + leftArg.getValue()
                                               + " of design entity "
                                               + toString(leftArg.getDesignEntity())
                                               + QueryValidatorInvalidFirstDesignEntityInRelation);
            default:
                continue;
        }
    }
}

void QueryValidator::validateWithClause() {
    for (auto clause : query->getWithClause()) {
        if (!clause->validateClause()) {
            throw QueryValidationException(QueryValidatorIncompatibleAttributeReference);
        }
    }
}

void QueryValidator::validateQuery() {
    validateNoDuplicateSynonymsInDeclaration();

    validateSynonymInSelectClauseWasDeclared();

    validateSuchThatClause();

    validatePatternClause();

    validateWithClause();
}
