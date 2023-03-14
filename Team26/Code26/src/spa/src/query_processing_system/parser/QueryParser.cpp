#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#include "QueryParser.h"
#include "common/parser/ShuntingYardParser.h"
#include "query_processing_system/parser/clause/pattern_clause/PatternClauseFactory.h"
#include "QueryParserUtil.h"

QueryParser::QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query) :
query(query), AbstractParser(tokens) {}

void QueryParser::parseAllDeclarations() {
    while (hasNext()) {
        if (!parseDeclaration()) {
            break;
        }
    }
}

// Structure: design-entity (',', synonym)*';'
// Example: variable v; assign a; procedure p; constant c; stmt s;
// Example: variable v1, v2, v3; assign a1, a2; procedure p, q;
bool QueryParser::parseDeclaration() {
    // Handle first token which is a Design Entity.
    std::shared_ptr<Token> designEntityToken;
    designEntityToken = getToken();
    std::string designEntityString = designEntityToken->getValue();
    DesignEntity designEntity;
    designEntity = getDesignEntityFromStr(designEntityString);
    if (!isValidDesignEntity(designEntity)) return false;
    getNext();  // Consumes first Design Entity token and moves to second token.

    // Handle second token which is a Synonym.
    std::shared_ptr<Token> synonymToken;
    synonymToken = getNext();
    Synonym firstSynonym = Synonym(synonymToken->getValue());
    std::vector<Synonym> synonyms;
    synonyms.push_back(firstSynonym);

    // While still at the same Design Entity, continue parsing the rest of the Synonym.
    while (!isValueOf(";")) {
        parseNext(",");
        std::shared_ptr<Token> nextSynonymToken;
        nextSynonymToken = getNext();
        Synonym nextSynonym = Synonym(nextSynonymToken->getValue());
        synonyms.push_back(nextSynonym);
    }

    parseNext(";");

    // Put Synonyms and their corresponding Design Entities into the Query wrapper object as one Declaration.
    for (const Synonym& syn : synonyms) {
        query->addDeclaration(syn, designEntity);
    }

    return true;
}

// Structure: select-cl: declaration* 'Select' synonym
// Example: Select v; Select a; Select p; Select c; Select s;
void QueryParser::parseSelectClause() {
    parseNext("Select");
    if (isValueOf("BOOLEAN") && !query->containsSynonymInDeclaration(getToken()->getValue())) {
        parseBooleanSelectClause();
    } else if (isTypeOf(TokenType::TOKEN_NAME)) {
        parseSingleSelectClause();
    } else if (isValueOf("<")) {
        parseTupleSelectClause();
    } else {
        throw QueryParserException(getNext()->getValue()
                                    + QueryParserInvalidSelectClause);
    }
//    for (const auto& item : *query->getSelectClause()->getSelectClauseItems()) {
//        std::shared_ptr<Synonym> synonym_ptr = std::get<std::shared_ptr<Synonym>>(item);
//        Synonym& synonym = *synonym_ptr;
//        std::cout << synonym.getIdent() << std::endl;
//    }
}

void QueryParser::parseSingleSelectClause() {
    SelectClauseItem selectClauseItem = parseReturnValue();
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);
}

void QueryParser::parseTupleSelectClause() {
    parseNext("<");
    SelectClauseItem selectClauseItem = parseReturnValue();
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);

    while (hasNext() && isValueOf(",")) {
        parseNext(",");
        SelectClauseItem item = parseReturnValue();
        selectClauseItems->push_back(item);
    }

    parseNext(">");
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems, SelectClauseReturnType::SYNONYM);
    query->setSelectClause(selectClauses);
}

void QueryParser::parseBooleanSelectClause() {
    std::shared_ptr<Token> booleanToken = getToken();
    parseNext("BOOLEAN");
    std::shared_ptr<SelectClause> selectClause;

    // Edge case: BOOLEAN in attribute reference
    if (isValueOf(".")) {
        AttributeReference attributeReference = parseAttributeReference(booleanToken);
        std::shared_ptr<std::vector<SelectClauseItem>> item;
        item->push_back(attributeReference);
        selectClause = std::make_shared<SelectClause>(item, SelectClauseReturnType::SYNONYM);
    } else {
        selectClause = std::make_shared<SelectClause>(SelectClauseReturnType::BOOLEAN);
    }

    query->setSelectClause(selectClause);
}

SelectClauseItem QueryParser::parseReturnValue() {
    std::shared_ptr<Token> synonymToken = getNext();
    if (synonymToken->getValue() == "_") {
        throw QueryParserException(QueryParserInvalidWildcardInSelectClause);
    }
    if (isValueOf(".")) {
        return parseAttributeReference(synonymToken);
    } else {
        return parseSynonym(synonymToken);
    }
}

std::shared_ptr<Synonym> QueryParser::parseSynonym(std::shared_ptr<Token> token) {
    auto synonym = std::make_shared<Synonym>(token->getValue());
    return synonym;
}

bool QueryParser::hasSuchThatClause() {
    if (!isValueOf("such")) {
        return false;
    } else {
        parseNext("such");
        parseNext("that");
        parseMultipleRelRef();
        return true;
    }
}

void QueryParser::parseMultipleRelRef() {
    parseRelRef();

    while (hasNext() && isValueOf("and")) {
        parseNext("and");
        parseRelRef();
    }
}

void QueryParser::parseRelRef() {
    auto relRefToken = getNext();
    std::string relRefString = relRefToken->getValue();
    if (isValueOf("*")) {
        std::shared_ptr<Token> asteriskToken = parseNext("*");
        relRefString += asteriskToken->getValue();
    }
    parseNext("(");
    Argument leftArgument = parseArgument();
    parseNext(",");
    Argument rightArgument = parseArgument();
    parseNext(")");
    auto relRefClause = SuchThatClauseFactory::createSuchThatClause(relRefString, leftArgument, rightArgument);
    query->addSuchThatClause(relRefClause);
}

Argument QueryParser::parseArgument() {
    if (isTypeOf(TokenType::TOKEN_INTEGER)) {
        // Token Type Integer means line number
        std::shared_ptr<Token> integerToken = parseNext(TokenType::TOKEN_INTEGER);
        std::string integerString = integerToken->getValue();
        Argument integerArgument(ArgumentType::NUMBER, integerString, DesignEntity::NONE);
        return integerArgument;
    } else if (isTypeOf(TokenType::TOKEN_NAME)) {
        // Token Type Name means Synonym
        std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
        std::string nameString = nameToken->getValue();
        DesignEntity designEntity = query->getSynonymDesignEntity(nameString);
        Argument nameArgument(ArgumentType::SYNONYM, nameString, designEntity);
        return nameArgument;
    } else if (isValueOf("_")) {
        // Wildcard
        std::shared_ptr<Token> wildcardToken = parseNext("_");
        std::string wildcardString = wildcardToken->getValue();
        Argument wildcardArgument(ArgumentType::WILDCARD, wildcardString, DesignEntity::NONE);
        return wildcardArgument;
    } else if (isValueOf("'")) {
        // Character String
        std::string ident = parseStringExpression();
        if (!QueryParserUtil::isValidIdent(ident)) {
            throw QueryParserException(ident + QueryParserInvalidIdent);
        }
        ident = parseShuntingYard(ident);
        Argument stringExpressionArgument(ArgumentType::CHARACTERSTRING, ident, DesignEntity::NONE);
        return stringExpressionArgument;
    } else {
        throw QueryParserException(getToken()->getValue() + QueryParserInvalidTokenForRelationshipArgument);
    }
}

bool QueryParser::hasPatternClause() {
    if (!isValueOf("pattern")) {
        return false;
    } else {
        parseNext("pattern");
        parseMultiplePatternClause();
        return true;
    }
}

void QueryParser::parseMultiplePatternClause() {
    parsePatternClause();

    while (hasNext() && isValueOf("and")) {
        parseNext("and");
        parsePatternClause();
    }
}

void QueryParser::parsePatternClause() {
//    Argument patternArg(ArgumentType::SYNONYM, "", DesignEntity::NONE);
    auto patternArg = parseArgument();
//    try {
//        patternArg = parseArgument();
//    } catch (SemanticException exception) {
//        throw SyntaxException("Invalid pattern argument");
//    }
    parseNext("(");
    // First argument can be variable synonyms, wildcard or character strings
    Argument leftArgument = parseArgument();
    parseNext(",");
    // Second argument can be wildcard or expression for exact/partial match
    StringExpression rightArgument = parseExpression();
    // Third argument must be wildcard for if pattern clause, otherwise should be )
    if (patternArg.getDesignEntity() == DesignEntity::ASSIGN || patternArg.getDesignEntity() == DesignEntity::WHILE) {
        if (isValueOf(",")) {
            throw SemanticException("Can only have 2 arguments");
        } else if (!isValueOf(")")) {
            throw SyntaxException("Invalid second argument");
        } else {
            parseNext(")");
        }
    } else if (patternArg.getDesignEntity() == DesignEntity::IF) {
        parseNextIfElseSemanticError(",", toString(patternArg.getDesignEntity())
                                          + QueryInvalidNumberOfPatternArguments);
        parseNext("_");
        parseNext(")");
    }
    PatternClause* patternClause =
            PatternClauseFactory::createPatternClause(patternArg, leftArgument, rightArgument);
    query->addPatternClause(patternClause);
}

StringExpression QueryParser::parseExpression() {
    // Expression for exact match (e.g. "x+y")
    bool isExactMatch = true;
    if (isValueOf("_")) {
        // Have wildcard means partial match
        // Expression for partial match (e.g. _"x+y"_)
        isExactMatch = false;
        parseNext("_");
        if (isValueOf("'")) {
            // String Expression
            std::string stringExpression = parseStringExpression();
            if (!QueryParserUtil::isValidStringExpression(stringExpression)) {
                throw QueryParserException(stringExpression + QueryParserInvalidStringExpression);
            }
            stringExpression = parseShuntingYard(stringExpression);
            parseNext("_");
            return StringExpression(isExactMatch, stringExpression);
        } else {
            // Wildcard
            return StringExpression(true);
        }
    } else {
        // Exact match
        std::string stringExpression = parseStringExpression();
        if (!QueryParserUtil::isValidStringExpression(stringExpression)) {
            throw QueryParserException(stringExpression + QueryParserInvalidStringExpression);
        }
        stringExpression = parseShuntingYard(stringExpression);
        if (isValueOf("_")) {
            throw QueryParserException(QueryParserUnexpectedToken);
        }
        return StringExpression(isExactMatch, stringExpression);
    }
}

std::string QueryParser::parseStringExpression() {
    parseNextIfElseSyntaxError("'", getToken()->getValue()
                                    + QueryValidatorIfWhilePatternRightArgWildcard);
    std::shared_ptr<Token> stringExpressionToken = parseNext(TokenType::TOKEN_STRING_EXPRESSION);
    std::string str = stringExpressionToken->getValue();
    parseNext("'");

//    str = parseShuntingYard(str);

    return str;
}

bool QueryParser::hasWithClause() {
    if (!isValueOf("with")) {
        return false;
    } else {
        parseNext("with");
        parseMultipleWithClause();
        return true;
    }
}

void QueryParser::parseWithClause() {
    Reference leftRef = parseReference();
    parseNextIfElseSyntaxError("=", getToken()->getValue()
                                    + QueryParserInvalidEqualSignInWithClause);
    Reference rightRef = parseReference();
    auto withClause = new WithClause(leftRef, rightRef);
    query->addWithClause(withClause);
}

void QueryParser::parseMultipleWithClause() {
    parseWithClause();

    while (hasNext() && isValueOf("and")) {
        parseNext("and");
        parseWithClause();
    }
}

AttributeReference QueryParser::parseAttributeReference(std::shared_ptr<Token> token) {
    parseNextIfElseSyntaxError(".", getToken()->getValue()
                                    + QueryParserInvalidAttributeRefInWithClause);
    std::string synonym = token->getValue();
    DesignEntity designEntity = query->getSynonymDesignEntity(synonym);
    std::shared_ptr<Token> attrRefToken = getNext();
    std::string attrRefString = attrRefToken->getValue();

    if (isValueOf("#")) {
        parseNext("#");
        attrRefString += "#";
    }

    AttributeReference attributeReference = AttributeReference(designEntity, synonym, attrRefString);
    if (attributeReference.isValidAttributeReference()) {
        return attributeReference;
    } else {
        throw QueryParserException(QueryValidatorInvalidAttributeReference);
    }
}

Reference QueryParser::parseReference() {
    if (isTypeOf(TokenType::TOKEN_INTEGER)) {
        std::string integer = getNext()->getValue();
        return Reference::createReference(std::stoi(integer));
    } else if (isValueOf("'")) {
        std::string ident = parseStringExpression();
        if (!QueryParserUtil::isValidIdent(ident)) {
            throw QueryParserException(ident + QueryParserInvalidIdent);
        }
        ident = parseShuntingYard(ident);
        return Reference::createReference(ident);
    } else if (isTypeOf(TokenType::TOKEN_NAME)) {
        std::shared_ptr<Token> attrRefToken = getNext();
        return Reference::createReference(parseAttributeReference(attrRefToken));
    } else {
        throw QueryParserException(getToken()->getValue() + QueryParserInvalidReferenceInWithClause);
    }
}

void QueryParser::parseEndingUnexpectedToken() {
    if (isValueOf(";")) {
        throw QueryParserException(QueryParserInvalidEndingSemicolon);
    } else {
        throw QueryParserException(QueryParserUnexpectedToken + getToken()->getValue());
    }
}

void QueryParser::parseNextIfElseSyntaxError(std::string nextValue, std::string errorMessage) {
    if (isValueOf(nextValue)) {
        parseNext(nextValue);
    } else {
        throw SyntaxException(errorMessage);
    }
}

void QueryParser::parseNextIfElseSemanticError(std::string nextValue, std::string errorMessage) {
    if (isValueOf(nextValue)) {
        parseNext(nextValue);
    } else {
        throw SemanticException(errorMessage);
    }
}

std::string QueryParser::parseShuntingYard(std::string str) {
    try {
        ShuntingYardParser::parse(str);
    } catch (ShuntingYardParserException& e) {
        throw QueryParserException(QueryParserUnbalancedStringExpression);
    }
    return str;
}

void QueryParser::parse() {
    // Firstly, parse Declaration.
    parseAllDeclarations();

    // Next, handle the Select Clause.
    parseSelectClause();

    while (hasNext()) {
        if (hasSuchThatClause()) {
            continue;
        }

        if (hasPatternClause()) {
            continue;
        }

        if (hasWithClause()) {
            continue;
        }

        parseEndingUnexpectedToken();
    }
}
