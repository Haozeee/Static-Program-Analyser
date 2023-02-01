#include "Declaration.h"

Declaration::Declaration(Synonym synonym, DesignEntity designEntity) : designEntity(designEntity), synonym(synonym) {}

DesignEntity Declaration::getDesignEntity() {
    return designEntity;
}

Synonym Declaration::getSynonym() {
    return synonym;
}

bool Declaration::operator==(const Declaration &other) const {
    return designEntity == other.designEntity && synonym == other.synonym;
}
