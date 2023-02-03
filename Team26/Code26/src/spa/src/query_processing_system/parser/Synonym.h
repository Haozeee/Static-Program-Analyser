#pragma once

#include <string>
#include <ostream>

// According to Basic PQL under Lexical Tokens:
// synonym : IDENT
// IDENT : LETTER ( LETTER | DIGIT )*
class Synonym {
 public:
    /**
     * Compares two Synonym objects.
     *
     * @param other Second Synonym object to be compared against.
     * @return Returns true if both Synonym objects are the same, false otherwise.
     */
    bool operator==(const Synonym &other) const;

    /**
     * Overloading operator<< to output Synonym as a stream object.
     *
     * @param ostream Output type for the object std::cout.
     * @param synonym Synonym object to be output.
     * @return
     */
    friend std::ostream& operator << (std::ostream& ostream, const Synonym& synonym);

    /**
     * A string which contains the identifier as defined by Basic PQL.
     */
    std::string ident;

    /**
     * Constructor for the Synonym.
     *
     * @param ident The identifier that is a Synonym.
     */
    explicit Synonym(std::string ident);

    std::string getIdent() const;

};
