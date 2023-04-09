#include "QueryValidator.h"

QueryValidator::QueryValidator(Query* query) : query(query) {}

void QueryValidator::validateDuplicateDeclarations() {
    std::unordered_set<std::string> declaration;
    for (const auto &d : query->getDeclarations()) {
        std::string synonym = Synonym::getSynonymIdentity(d->getSynonym());
        if (declaration.find(synonym) != declaration.end()) {
            throw SemanticException(QueryValidatorDuplicatedSynonymInDeclaration + synonym);
        }
        declaration.insert(synonym);
    }
}

void QueryValidator::validateSynonymInSelectClauseWasDeclared() {
    std::unordered_set<std::string> declarationSynonyms = getDeclarationSynonyms();

    if (query->isBooleanQuery()) {
        return;
    }

    auto selectClauseItems = query->getSelectClauseItems();
    std::unordered_set<std::string> selectClauseSynonyms;
    for (auto item : *selectClauseItems) {
        if (std::holds_alternative<std::shared_ptr<Synonym>>(item)) {
            std::string selectClauseSynonym = SelectClause::getSynonym(item);
            selectClauseSynonyms.insert(selectClauseSynonym);
        } else {
            AttributeReference attributeReference = std::get<AttributeReference>(item);
            std::string attributeReferenceSynonym = attributeReference.getSynonym();
            selectClauseSynonyms.insert(attributeReferenceSynonym);
        }
    }

    if (!containsSelectClauseSynonymInDeclaration(declarationSynonyms, selectClauseSynonyms)) {
        throw SemanticException(QueryValidatorUndeclaredSelectClauseSynonym + *selectClauseSynonyms.begin());
    }
}

std::unordered_set<std::string> QueryValidator::getDeclarationSynonyms() {
    std::vector<std::shared_ptr<Declaration>> declarations;
    declarations = query->getDeclarations();
    std::unordered_set<std::string> declarationSynonyms;
    for (auto it = declarations.begin(); it != declarations.end(); ++it) {
        auto declaration = *it;
        std::string declarationSynonym = Synonym::getSynonymIdentity(declaration->getSynonym());
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
                throw SyntaxException(leftArg.getValue()
                                               + QueryValidatorInvalidFirstArgumentTypeInRelation);
            case SuchThatClauseValidationResult::INVALID_RIGHT_ARG_TYPE:
                throw SyntaxException(rightArg.getValue()
                                               + QueryValidatorInvalidSecondArgumentTypeInRelation);
            case SuchThatClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY:
                throw SemanticException("The synonym "
                                           + leftArg.getValue()
                                           + " of design entity "
                                           + toString(leftArg.getDesignEntity())
                                           + QueryValidatorInvalidFirstDesignEntityInRelation);
            case SuchThatClauseValidationResult::INVALID_RIGHT_DESIGN_ENTITY:
                throw SemanticException("The synonym "
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
        if (patternArg.getDesignEntity() == DesignEntity::WHILE) {
            if (!rightArg.isWildCard()) {
                throw SemanticException(rightArg.getExpression()
                                          + QueryValidatorIfWhilePatternRightArgWildcard);
            }
        }
        if (patternArg.getDesignEntity() == DesignEntity::IF) {
            if (!rightArg.isWildCard()) {
                throw SyntaxException(rightArg.getExpression()
                                        + QueryValidatorIfWhilePatternRightArgWildcard);
            }
        }
        switch (validationResult) {
            case PatternClauseValidationResult::INVALID_LEFT_ARG_TYPE:
                throw SyntaxException(leftArg.getValue()
                                           + QueryValidatorInvalidFirstArgumentTypeInRelation);
            case PatternClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY:
                throw SemanticException("The synonym "
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
            throw SemanticException(QueryValidatorIncompatibleAttributeReference);
        }
    }
}

void QueryValidator::validateQuery() {
    validateDuplicateDeclarations();

    validateSynonymInSelectClauseWasDeclared();

    validateSuchThatClause();

    validatePatternClause();

    validateWithClause();
}
