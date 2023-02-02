#pragma once

#include <string>

// According to Basic PQL under Lexical Tokens:
// synonym : IDENT
// IDENT : LETTER ( LETTER | DIGIT )*
class Synonym {
 public:
    std::string ident;
    explicit Synonym(std::string ident);

    std::string toString();

    bool operator==(const Synonym &other) const;

    friend std::ostream& operator << (std::ostream& os, const Synonym& syn);

    std::size_t hash() const;
};
