#pragma once

#include "common/tokens/Token.h"

#include <vector>
#include <string>

/**
 * The tokenizer class tokenize an input stream into a token list.
 * */
class Tokenizer {

private:
    /**
     * This function loads the next punctuation from the stream to the currentToken.
     * */
    virtual void readPunctuation() = 0;

    /**
     * This functions checks if there exist leading zeros the current token.
     *
     * @return Returns true if there a leading zero in current token.
     * */
     bool hasLeadingZero();

protected:
    /**
     * The incoming stream to read from.
     * */
    std::istream* istream;

    /**
     * Temporary storage for current token.
     * */
    std::string currentToken;

    /**
     * List of tokens that are tokenized.
     * */
    std::vector<std::shared_ptr<Token>> tokens;

    /**
     * Extract and return the next character in the input sequence.
     *
     * @return The first character read or end-of-file value if stream is empty.
     * */
    char nextChar();

    /**
     * Returns the next character in the input sequence without extracting it.
     *
     * @returns The next character in the input sequence, as a vale of type char.
     * */
    char peekChar();

    /**
     * This function loads the next INTEGER from the stream to the currentToken.
     * */
    void readInteger();

    /**
     * This function loads the next NAME (or INDENT) from the stream to the currentToken.
     * */
    void readName();

    /**
      * Get the currentToken value.
      *
      * @return The token that current token that has been tokenized;
      * */
    std::string getCurrentToken();

    /**
     * Add token to the the token list.
     *
     * @param token The token to be added.
     * */
    void addToken(std::shared_ptr<Token> token);

    /**
     * Get all tokens in the token list
     *
     * @return The tokens list.
     * */
    std::vector<std::shared_ptr<Token>> getTokens();

public:

    /**
     * Constructor for the Source Processor initialization.
     *
     * @param stream The input SIMPLE program as a stream to be tokenized.
     * */
    explicit Tokenizer(std::istream* stream);

    /**
     * Constructor for the Query Processing Subsystem initialization.
     *
     * @param stream The query to be tokenized.
     * */
    explicit Tokenizer(const std::string& query);

    /**
     * This functions tokenizes the input stream.
     *
     * @return The token list after tokenizing the input stream.
     * */
    virtual std::vector<std::shared_ptr<Token>> tokenize() = 0;
};
