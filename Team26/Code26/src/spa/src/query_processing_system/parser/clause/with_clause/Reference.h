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
    /**
     * Factory method to create a Reference.
     */
    static Reference createReference(std::variant<AttributeReference, int, std::string>);

    /**
    * If the reference is an attribute, get its identity. Else, the function throws an error.
    */
    std::string getAttributeIdentity();

    /**
    * If the reference is an attribute, get its design entity. Else, the function throws an error.
    */
    DesignEntity getAttributeDesignEntity();

    bool isStringReference();

    bool isIntReference();

    ReferenceType getReferenceType();

    std::variant<AttributeReference, int, std::string> getValue();

    bool operator==(const Reference& other) const;

    static std::string toString(Reference);
};
