#include "Reference.h"

Reference::Reference(ReferenceType ref, std::variant<AttributeReference, int, std::string> value)
    : referenceType(ref), value(std::move(value)) {}

Reference Reference::createReference(std::variant<AttributeReference, int, std::string> value) {
    if (std::holds_alternative<int>(value)) {
        return {ReferenceType::INTEGER, value};
    } else if (std::holds_alternative<std::string>(value)) {
        return {ReferenceType::IDENT, value};
    } else {
        return {ReferenceType::ATTR_REF, value};
    }
}

std::string Reference::getAttributeIdentity() {
    return std::get<AttributeReference>(value).getSynonym();
}

DesignEntity Reference::getAttributeDesignEntity() {
    return std::get<AttributeReference>(value).getDesignEntity();
}

bool Reference::isStringReference() {
    return referenceType == ReferenceType::IDENT || (referenceType == ReferenceType::ATTR_REF &&
        std::get<AttributeReference>(value).isStringAttributeReference());
}

bool Reference::isIntReference() {
    return referenceType == ReferenceType::INTEGER || (referenceType == ReferenceType::ATTR_REF &&
        std::get<AttributeReference>(value).isIntAttributeReference());
}

ReferenceType Reference::getReferenceType() {
    return referenceType;
}

std::variant<AttributeReference, int, std::string> Reference::getValue() {
    return value;
}

bool Reference::operator==(const Reference& other) const {
    return this->referenceType == other.referenceType && this->value == other.value;
}
