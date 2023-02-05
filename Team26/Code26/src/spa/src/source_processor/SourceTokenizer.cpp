#include "SourceTokenizer.h"
#include <string>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include "common/tokens/EndOfFileToken.h"
#include "common/tokens/NameToken.h"
#include "common/tokens/IntegerToken.h"
#include "common/tokens/SpecialCharToken.h"

SourceTokenizer::SourceTokenizer(std::istream* stream) : Tokenizer(stream) {}

std::unordered_set<std::string> specialChar({"{", "}", ";", "(", ")", "=", ">", "<", "+", "-", "*", "/", "%", "!"});
std::unordered_set<std::string> validLogicalOps({"&&", "||", ">=", "<=", "==", "!="});
std::unordered_set<std::string> firstOp({"&", "|", ">", "<", "=", "!"});
std::unordered_set<char> secondOp({'&', '|', '='});

bool SourceTokenizer::isValidSpecialChar() {
    return (specialChar.find(getCurrentToken()) != specialChar.end());
}

bool SourceTokenizer::isPossibleLogicalOp() {
    return (firstOp.find(getCurrentToken()) != firstOp.end() && secondOp.find(peekChar()) != secondOp.end());
}

bool SourceTokenizer::isValidLogicalOp() {
    currentToken += nextChar();
    return validLogicalOps.find(getCurrentToken()) != validLogicalOps.end();
}

void SourceTokenizer::readSpecialChar() {
    if (isValidSpecialChar()) /* valid special char */ {
        if (isPossibleLogicalOp() && !isValidLogicalOp()) /* invalid logical operation */ {
            // TODO(zhengteck): throw exception
        }
    } else /* invalid special char */ {
        // TODO(zhengteck): throw exception
    }
}

std::vector<std::shared_ptr<Token>> SourceTokenizer::tokenize() {
    char c = 0;

    while (!istream->eof()) {
        c = nextChar();

        if (c == EOF) {
            addToken(std::make_shared<EndOfFileToken>());
            break;
        }

        currentToken += c;
        if (isspace(c)) {
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

    // TODO(zhengteck): Remove when not required
    // FOR DEBUGGING
    //    for (const auto& element : tokens) {
    //        std::cerr << element->getValue() << std::endl;
    //    }

    return tokens;
}
