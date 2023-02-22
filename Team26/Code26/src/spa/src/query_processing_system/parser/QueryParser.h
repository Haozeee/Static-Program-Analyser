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

    /**
     * Parses a Synonym.
     *
     * @return Returns a smart pointer managing a Synonym.
     */
    std::shared_ptr<Synonym> parseSynonym(std::shared_ptr<Token>);

    /**
     * Parses Such That Clause if any.
     */
    bool parseIfSuchThatClause();

    /**
     * Handles parsing of relRef:
     * Follows | FollowsT | Parent | ParentT | UsesS | UsesP | ModifiesS | ModifiesP
     */
    void parseRelRef();

    void parseMultipleRelRef();

    /**
     * Parse Arguments of any relRef relationships.
     * Example: Follows(1, 2) Left argument is 1 and right argument is 2.
     *
     * @return Left or right Argument of relRef.
     */
    Argument parseArgument();

    /**
     * Parses Assign Pattern Clause if any.
     */
    bool parseIfAssignPatternClause();

    void parseAssignPatternClause();

    StringExpression parseExpression();

    std::string parseStringExpression();
    /**
     * Parses ending semicolon if any and throws exception.
     */
    void parseEndingUnexpectedToken();

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
