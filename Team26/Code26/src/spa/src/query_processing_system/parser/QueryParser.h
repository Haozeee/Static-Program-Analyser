#pragma once

#include <memory>
#include <string>
#include <vector>

#include "query_processing_system/parser/Query.h"
#include "common/parser/AbstractParser.h"
#include "Argument.h"
#include "Query.h"
#include "StringExpression.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"
#include "query_processing_system/parser/clause/such_that_clause/SuchThatClauseFactory.h"


class QueryParser : public AbstractParser {
 private:
    /**
     * Query wrapper object.
     */
    Query* query;

    /**
     * Parses all Declarations regardless of Design Entity.
     */
    void parseAllDeclarations();

    /**
     * Parses Declarations of the same Design Entity and adds it into the Query wrapper object.
     */
    bool parseDeclaration();

    /**
     * Parses a Select Clause.
     */
    void parseSelectClause();

    void parseSingleSelectClause();

    void parseTupleSelectClause();

    SelectClauseItem parseReturnValue();

    void parseBooleanSelectClause();

    /**
     * Parses a Synonym.
     *
     * @return Returns a smart pointer managing a Synonym.
     */
    static std::shared_ptr<Synonym> parseSynonym(std::shared_ptr<Token>);

    /**
     * Parses Such That Clause if any.
     */
    bool hasSuchThatClause();

    /**
     * Handles parsing of relRef:
     * Follows | FollowsT | Parent | ParentT | UsesS | UsesP | ModifiesS | ModifiesP
     */
    void parseSuchThat();

    void parseMultipleSuchThat();

    /**
     * Parse Arguments of any relRef relationships.
     * Example: Follows(1, 2) Left argument is 1 and right argument is 2.
     *
     * @return Left or right Argument of relRef.
     */
    Argument parseArgument();

    /**
     * Parses Pattern Clause if any.
     */
    bool hasPatternClause();

    void parsePatternClause();

    void parseMultiplePatternClause();

    StringExpression parseExpression();

    std::string parseStringExpression();

    /**
     * Parses With Clause if any.
     */
    bool hasWithClause();

    void parseWithClause();

    void parseMultipleWithClause();

    AttributeReference parseAttributeReference(std::shared_ptr<Token>);

    Reference parseReference();

    /**
     * Parses ending semicolon if any and throws exception.
     */
    void parseEndingUnexpectedToken();

    void parseNextIfElseSyntaxError(std::string nextValue, std::string errorMessage);

    void parseNextIfElseSemanticError(std::string nextValue, std::string errorMessage);

    std::string parseShuntingYard(std::string);

    std::string referenceToString(Reference);

 public:
    /**
     * Constructor for the query parser.
     *
     * @param tokens The list of tokens to be parsed.
     * @param query The Query wrapper object to be updated.
     */
    explicit QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query);

    /**
     * Parses tokens and returns Query wrapper object.
     */
    void parse() override;
};
