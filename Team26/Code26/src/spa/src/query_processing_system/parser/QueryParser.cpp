#include "QueryParser.h"

QueryParser::QueryParser(std::vector<std::shared_ptr<Token>> tokens, Query* query) : query(query), Parser(tokens) {}

