#include "QueryTokenizer.h"
#include <unordered_set>
#include <string>
#include <stdexcept>
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/StringExpressionToken.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"

std::unordered_set<std::string> specialChars({";", ",", "_", "=", "*", "(", ")", "<", ">", "#", "."});

QueryTokenizer::QueryTokenizer(const std::string& query) : AbstractTokenizer(query) {}

void QueryTokenizer::readSpecialChar() {
    if (specialChars.find(getCurrentToken()) == specialChars.end()) {
        // Invalid punctuation
        throw QueryTokenizerException(getCurrentToken() + QueryTokenizerInvalidPunctuation);
    }
}

void QueryTokenizer::readStringExpression() {
    tokens.push_back(std::make_shared<SpecialCharToken>("'"));
    currentToken = "";

    char c = peekChar();
    while (c != EOF && c != '"') {
        currentToken += nextChar();
        c = peekChar();
    }
    addToken(std::make_shared<StringExpressionToken>(getCurrentToken()));

    if (nextChar() == '"') {
        tokens.push_back(std::make_shared<SpecialCharToken>("'"));
    }
}

std::vector<std::shared_ptr<Token>> QueryTokenizer::tokenize() {
    char c = nextChar();

    while (c != EOF) {
        currentToken += c;
        if (c == '\n' || isspace(c)) {
        } else if (isalpha(c)) {
            readName();
            addToken(std::make_shared<NameToken>(getCurrentToken()));
        } else if (isdigit(c)) {
            readInteger();
            addToken(std::make_shared<IntegerToken>(getCurrentToken()));
        } else if (c == '"') {
            readStringExpression();
        } else {
            readSpecialChar();
            addToken(std::make_shared<SpecialCharToken>(getCurrentToken()));
        }

        c = nextChar();
        currentToken = "";
    }

    // Add EOF Token
    addToken(std::make_shared<EndOfFileToken>());
    return tokens;
}
