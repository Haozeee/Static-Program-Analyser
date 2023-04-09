#include "Synonym.h"

bool Synonym::operator==(const Synonym &other) const {
    return ident == other.ident;
}

std::ostream& operator << (std::ostream& os, const Synonym& syn) {
    os << syn.ident;
    return os;
}

Synonym::Synonym(std::string ident) : ident(ident) {}

std::string Synonym::getIdent() const {
    return ident;
}

std::string Synonym::getSynonymIdentity(const Synonym& synonym) {
    return synonym.getIdent();
}
