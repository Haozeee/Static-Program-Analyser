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
    for (auto suchThatClause : query->getSuchThatClauses()) {
        ValidArgumentType validArgType = suchThatClause->getValidArgumentType();

        // Validate First Argument Type
        ArgTypeIndex validFirstArgType = validArgType.first;  // Will return {0, 1, 2} or {0, 1, 3}
        Argument parsedFirstArg = suchThatClause->getLeftArg();
        ArgumentType parsedFirstArgType = parsedFirstArg.getArgumentType();
        int parsedFirstArgTypeIndex = parsedFirstArg.getArgumentTypeIndex(parsedFirstArgType);
//        for (const auto& value : validFirstArgType) {
//            std::cout << "validFirstArgType = " << value << std::endl;
//        }
//        std::cout << "parsedFirstArgType = " << parsedFirstArg.getArgumentTypeIndex(parsedFirstArgType) << std::endl;
        if (validFirstArgType.find(parsedFirstArgTypeIndex) == validFirstArgType.end()) {
            throw QueryValidationException(parsedFirstArg.getValue()
                                            + QueryValidatorInvalidFirstArgumentTypeInRelation);
        }

        // Validate Second Argument Type
        ArgTypeIndex validSecondArgType = validArgType.second;  // Will return {0, 1, 2} or {0, 1, 3}
        Argument parsedSecondArg = suchThatClause->getRightArg();
        ArgumentType parsedSecondArgType = parsedSecondArg.getArgumentType();
        int parsedSecondArgTypeIndex = parsedSecondArg.getArgumentTypeIndex(parsedSecondArgType);
//        for (const auto& value : validSecondArgType) {
//            std::cout << "validSecondArgType = " << value << std::endl;
//        }
//        std::cout << "validSecondArgType = " << parsedSecondArg.getArgumentTypeIndex(parsedSecondArgType) << std::endl;
        if (validSecondArgType.find(parsedSecondArgTypeIndex) == validSecondArgType.end()) {
            throw QueryValidationException(parsedSecondArg.getValue()
                                           + QueryValidatorInvalidSecondArgumentTypeInRelation);
        }

        ValidDesignEntity validDesignEntity = suchThatClause->getValidDesignEntity();
        // Validate First Design Entity
        std::unordered_set<DesignEntity> firstDesignEntitySet = validDesignEntity.first;
//        for (const auto& value : firstDesignEntitySet) {
//            std::cout << "firstDesignEntitySet = " << toString(value) << std::endl;
//        }
        if (parsedFirstArg.getArgumentType() == ArgumentType::SYNONYM) {
            DesignEntity designEntity = query->getSynonymDesignEntity(parsedFirstArg.getValue());
//            std::cout << "designEntity = " << toString(designEntity) << std::endl;
            if (firstDesignEntitySet.find(designEntity) == firstDesignEntitySet.end()) {
                throw QueryValidationException(QueryValidatorInvalidFirstDesignEntityInRelation1
                                                + parsedFirstArg.getValue()
                                                + QueryValidatorInvalidFirstDesignEntityInRelation2
                                                + toString(parsedFirstArg.getDesignEntity())
                                                + QueryValidatorInvalidFirstDesignEntityInRelation);
            }
        }

        // Validate Second Design Entity
        std::unordered_set<DesignEntity> secondDesignEntitySet = validDesignEntity.second;
//        for (const auto& value : secondDesignEntitySet) {
//            std::cout << "secondDesignEntitySet = " << toString(value) << std::endl;
//        }
        if (parsedSecondArg.getArgumentType() == ArgumentType::SYNONYM) {
            DesignEntity designEntity = query->getSynonymDesignEntity(parsedSecondArg.getValue());
//            std::cout << "designEntity = " << toString(designEntity) << std::endl;
            if (secondDesignEntitySet.find(designEntity) == secondDesignEntitySet.end()) {
                throw QueryValidationException(QueryValidatorInvalidFirstDesignEntityInRelation1
                                               + parsedSecondArg.getValue()
                                               + QueryValidatorInvalidFirstDesignEntityInRelation2
                                               + toString(parsedSecondArg.getDesignEntity())
                                               + QueryValidatorInvalidSecondDesignEntityInRelation);
            }
        }
    }
}

void QueryValidator::validateQuery() {
    validateNoDuplicateSynonymsInDeclaration();

    validateSynonymInSelectClauseWasDeclared();

    validateSuchThatClause();
}
