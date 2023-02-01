#pragma once
#include <memory>
#include <vector>
#include "query_processing_system/parser/Query.h"
#include "common/Parser.h"


class QueryParser : public Parser {
 private:
    /**
     * Query wrapper object
     */
    Query* query;

 public:
    /**
     * Constructor for the query parser.
     * @param tokens The list of tokens to be parsed.
     * @param query The Query wrapper object to be updated.
     */
    explicit QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query);

    /**
     * Parse tokens and return Query wrapper object.
     */
    void parse();
};
