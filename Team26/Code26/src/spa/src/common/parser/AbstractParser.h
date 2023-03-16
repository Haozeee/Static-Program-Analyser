#pragma once

#include <vector>
#include <memory>
#include <string>
#include "common/tokenizer/token/Token.h"

class AbstractParser {
 protected:
    /**
     * The index of the current token.
     * */
    int index = 0;

    /**
     * List of tokens that are tokenized.
     * */
    std::vector<std::shared_ptr<Token>> tokens;

    /**
     * This function check if a token exists at the next index.
     * Note: Does not include EOF token (tokens[tokens.size()-1] should be EOF token).
     *
     * @return Returns true if a token exists, else false.
     * */
    bool hasNext();

    /**
     * This function compares the type of token at the current index with the given type.
     *
     * @param type The type of token to be compared.
     * @return Returns true if the type of the next token matches the given type.
     * */
    bool isTypeOf(TokenType type);

    /**
     * This function compares the value of the token at current index with the given value.
     *
     * @param value The value to be compared.
     * @return Returns true if value of the next token matches the given value.
     * */
    bool isValueOf(const std::string& value);

    /**
    * Returns the token at the current index.
    *
    *
    * @returns The token at current index.
    * */
    std::shared_ptr<Token> getToken();

    /**
     * Increment to next index and return the token in that index.
     *
     * @return The next token in the token list.
     * */
    std::shared_ptr<Token> getNext();

    /**
     * Extract and return the end-of-file token (last token) in the token list.
     *
     * @return The end-of-file token.
     * */
    std::shared_ptr<Token> getEOF();

    /**
     * Check the type of current token and return value of next token if it matches.
     *
     * @param type The type of token to be compared.
     * @return The next token in the token list.
     * */
    std::shared_ptr<Token> parseNext(TokenType type);

    /**
     * Check value of current token and return value of next token if it matches.
     *
     * @param value The value to be compared.
     * @return The next token in the token list.
     * */
    std::shared_ptr<Token> parseNext(const std::string& value);

 public:
    /**
    * Constructor for the parser.
    * Note: std::move is being used in implementation for optimisation.
    *
    * @param tokens The token list to be parse.
    * */
    explicit AbstractParser(std::vector<std::shared_ptr<Token>> tokens);

    virtual void parse() = 0;
};

