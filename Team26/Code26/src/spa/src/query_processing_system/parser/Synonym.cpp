#include "Synonym.h"

Synonym::Synonym(std::string ident) : ident(ident) {}

bool Synonym::operator==(const Synonym &other) const {
    return ident == other.ident;
}
