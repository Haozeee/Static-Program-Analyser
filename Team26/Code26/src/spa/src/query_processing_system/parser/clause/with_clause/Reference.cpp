#include "Reference.h"

Reference::Reference(ReferenceType ref, std::variant<AttributeReference, int, std::string> value)
    : referenceType(ref), value(std::move(value)) {}

Reference Reference::createIntegerReference(int intRef) {
    return {ReferenceType::INTEGER, intRef};
}

Reference Reference::createIdentityReference(std::string identity) {
    return {ReferenceType::IDENT, identity};
}

Reference Reference::createAttributeReference(AttributeReference attrRef) {
    return {ReferenceType::ATTR_REF, attrRef};
}

bool Reference::isStringReference() {
    return referenceType == ReferenceType::IDENT || (referenceType == ReferenceType::ATTR_REF &&
        std::get<AttributeReference>(value).isStringAttributeReference());
}

bool Reference::isIntReference() {
    return referenceType == ReferenceType::INTEGER || (referenceType == ReferenceType::ATTR_REF &&
        std::get<AttributeReference>(value).isIntAttributeReference());
}
