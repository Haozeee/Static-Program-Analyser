#pragma once

#include <utility>
#include <string>
#include <variant>
#include "AttributeReference.h"
#include "../../Synonym.h"
#include "../../DesignEntity.h"

enum class ReferenceType {
    IDENT,
    INTEGER,
    ATTR_REF
};

class Reference {
 private:
    ReferenceType referenceType;

    std::variant<AttributeReference, int, std::string> value;

    Reference(ReferenceType ref, std::variant<AttributeReference, int, std::string> value);

 public:
    static Reference createIdentityReference(std::string identity);

    static Reference createIntegerReference(int intRef);

    static Reference createAttributeReference(AttributeReference attrRef);

    bool isStringReference();

    bool isIntReference();
};
