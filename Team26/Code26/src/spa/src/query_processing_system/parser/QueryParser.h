#pragma once

#include <memory>
#include <vector>
#include "query_processing_system/parser/Query.h"
#include "common/Parser.h"


class QueryParser : public Parser {
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
    void parse();
};
