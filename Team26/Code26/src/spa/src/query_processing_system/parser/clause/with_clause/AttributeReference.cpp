#include "AttributeReference.h"

AttributeReference::AttributeReference(DesignEntity designEntity, std::string synonym, std::string attributeName)
    : designEntity(designEntity), synonym(synonym), attributeName(attributeName) {}

bool AttributeReference::isStringAttributeReference() {
    auto it = validStringAttributes.find(designEntity);
    return it != validStringAttributes.end() && it->second == attributeName;
}


bool AttributeReference::isIntAttributeReference() {
    auto it = validIntAttributes.find(designEntity);
    return it != validIntAttributes.end() && it->second == attributeName;
}

bool AttributeReference::isValidAttributeReference() {
    return isStringAttributeReference() || isIntAttributeReference();
}
