#include "Tokenizer.h"

#include <unordered_set>
#include <sstream>
#include <string>
#include "source_processor/exception/SourceException.h"
#include "source_processor/exception/SourceProcessorExceptionMessage.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"

Tokenizer::Tokenizer(std::istream* stream) : AbstractTokenizer(stream) {}

std::unordered_set<std::string> specialChar({"{", "}", ";", "(", ")", "=", ">", "<", "+", "-", "*", "/", "%", "!",
                                             "&", "|"});
std::unordered_set<std::string> validLogicalOps({"&&", "||", ">=", "<=", "==", "!="});
std::unordered_set<std::string> firstOp({"&", "|", ">", "<", "=", "!"});
std::unordered_set<char> secondOp({'&', '|', '='});

bool Tokenizer::isValidSpecialChar() {
    return (specialChar.find(getCurrentToken()) != specialChar.end());
}

bool Tokenizer::isPossibleLogicalOp() {
    return (firstOp.find(getCurrentToken()) != firstOp.end() && secondOp.find(peekChar()) != secondOp.end());
}

bool Tokenizer::isValidLogicalOp() {
    currentToken += nextChar();
    return validLogicalOps.find(getCurrentToken()) != validLogicalOps.end();
}

void Tokenizer::readSpecialChar() {
    if (isValidSpecialChar()) /* valid special char */ {
        if (isPossibleLogicalOp() && !isValidLogicalOp()) /* invalid logical operation */ {
            throw SourceTokenizerException(TokenizerInvalidLogicalOpExceptionMessage);
        }
    } else /* invalid special char */ {
        throw SourceTokenizerException(TokenizerSpecialCharExceptionMessage);
    }
}

std::vector<std::shared_ptr<Token>> Tokenizer::tokenize() {
    while (!istream->eof()) {
        char c = nextChar();

        if (c == EOF) {
            addToken(std::make_shared<EndOfFileToken>());
            break;
        }

        currentToken += c;
        if (isspace(c)) {
            // do nothing
        } else if (isalpha(c)) {
            readName();
            addToken(std::make_shared<NameToken>(getCurrentToken()));
        } else if (isdigit(c)) {
            readInteger();
            addToken(std::make_shared<IntegerToken>(getCurrentToken()));
        } else {
            readSpecialChar();
            addToken(std::make_shared<SpecialCharToken>(getCurrentToken()));
        }
        currentToken = "";
    }

    return tokens;
}
