#include <string>
#include <iostream>
#include "QueryParser.h"

QueryParser::QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query) :
query(query), Parser(tokens) {}

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
    getNext();  // Consumes first Design Entity token and moves to second token.
    if (!isValidDesignEntity(designEntity)) return false;

    // Handle second token which is a Synonym.
    std::shared_ptr<Token> synonymToken;
    synonymToken = getNext();
    Synonym firstSynonym = Synonym(synonymToken->getValue());
    std::string synonymString = synonymToken->getValue();
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
    std::cout << selectClauseItems << "\n";
    auto selectClauses = std::make_shared<SelectClause>(selectClauseItems);
    query->setSelectClause(selectClauses);
}

std::shared_ptr<Synonym> QueryParser::parseSynonym(std::shared_ptr<Token> token) {
    auto synonym = std::make_shared<Synonym>(token->getValue());
    return synonym;
}

void QueryParser::parse() {
    // First, parse Declaration.
    parseAllDeclarations();

    // Next, handle the Select Clause.
    parseSelectClause();
}

