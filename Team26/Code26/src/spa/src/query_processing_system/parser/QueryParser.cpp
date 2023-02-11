#include <string>
#include <iostream>

#include "QueryParser.h"
#include "query_processing_system/parser/clause/pattern_clause/AssignPatternClauseFactory.h"

QueryParser::QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query) :
query(query), AbstractParser(tokens) {}

void QueryParser::parseAllDeclarations() {
    while (hasNext()) {
        if (!parseDeclaration()) {
            break;
        }
    }
    parseNext("Select");
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
    std::shared_ptr<Token> synonymToken = getNext();
    SelectClauseItem selectClauseItem = parseSynonym(synonymToken);
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems);
    query->setSelectClause(selectClauses);
}

std::shared_ptr<Synonym> QueryParser::parseSynonym(std::shared_ptr<Token> token) {
    auto synonym = std::make_shared<Synonym>(token->getValue());
    return synonym;
}

bool QueryParser::isSuchThatClause() {
    if (!isValueOf("such")) {
        return false;
    } else {
        parseNext("such");
        parseNext("that");
        parseRelRef();
        return true;
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
        std::string stringExpression = parseStringExpression(); 
        Argument stringExpressionArgument(ArgumentType::CHARACTERSTRING, stringExpression, DesignEntity::NONE);
        return stringExpressionArgument; 
    } else {
        throw QueryParserException(getToken()->getValue() + QueryParserInvalidTokenForRelationshipArgument);
    }
}

bool QueryParser::isAssignPatternClause() {
    if (!isValueOf("pattern")) {
        return false;
    } else {
        parseNext("pattern");
        parseAssignPatternClause();
        return true;
    }
}

void QueryParser::parseAssignPatternClause() {
    std::shared_ptr<Token> assignToken = parseNext(TokenType::TOKEN_NAME);
    std::string assignString = assignToken->getValue();
    DesignEntity assignDesignEntity = query->getSynonymDesignEntity(assignString);
    if (assignDesignEntity != DesignEntity::ASSIGN) {
        throw QueryParserException(assignString + QueryParserInvalidAssignPatternSynonym);
    }
    parseNext("(");
    // First argument can be variable synonyms, wildcard or character strings
    Argument leftArgument = parseArgument();
    parseNext(",");
    // Second argument can be wildcard or expression for exact/partial match
    std::variant<Wildcard, StringExpression> rightArgument = parseExpression();
    parseNext(")");
/*
 * Add create pattern clause here
 */
}

std::variant<Wildcard, StringExpression> QueryParser::parseExpression() {
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
            parseNext("_");
            return StringExpression(isExactMatch, stringExpression);
        } else {
            // Wildcard
            return Wildcard();
        }
    }  else {
        // Exact match
        std::string stringExpression = parseStringExpression();
        return StringExpression(isExactMatch, stringExpression); 
    }
}

std::string QueryParser::parseStringExpression() {
    parseNext("'");
    std::shared_ptr<Token> stringExpressionToken = parseNext(TokenType::TOKEN_STRING_EXPRESSION);
    std::string stringExpression = stringExpressionToken->getValue();
    parseNext("'");
    return stringExpression;
}

void QueryParser::parseEndingUnexpectedToken() {
    if (isValueOf(";")) {
        throw QueryParserException(QueryParserInvalidEndingSemicolon);
    } else {
        throw QueryParserException(QueryParserUnexpectedToken + getToken()->getValue());
    }
}

void QueryParser::parse() {
    // First, parse Declaration.
    parseAllDeclarations();

    // Next, handle the Select Clause.
    parseSelectClause();

    while (hasNext()) {
        if (isSuchThatClause()) {
            continue;
        }

        if (isAssignPatternClause()) {
            continue;
        }

        parseEndingUnexpectedToken();
    }
}
