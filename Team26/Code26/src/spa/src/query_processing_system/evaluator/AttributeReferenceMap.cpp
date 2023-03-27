#include "AttributeReferenceMap.h"

void mapAttribute(const AttributeReference& attributeRef, StringVector &synonymValues,
                  std::shared_ptr<ISourceReader> storage) {
    std::unordered_map<int, std::unordered_set<std::string>> relationship;
    std::unordered_set<int> interestedValues;
    auto de = attributeRef.getDesignEntity();
    auto attrName = attributeRef.getAttributeName();

    if (de == DesignEntity::READ && attrName == varName) {
        interestedValues = storage->getIntEntitiesFromPkb(DesignEntity::READ);
        relationship = storage->getModifiesSMap(interestedValues);
        mapStatementToVariable(synonymValues, relationship);
    } else if (de == DesignEntity::PRINT && attrName == varName) {
        interestedValues = storage->getIntEntitiesFromPkb(DesignEntity::PRINT);
        relationship = storage->getUsesSMap(interestedValues);
        mapStatementToVariable(synonymValues, relationship);
    } else if (de == DesignEntity::CALL && attrName == procName) {
        interestedValues = storage->getIntEntitiesFromPkb(DesignEntity::CALL);
        relationship = storage->getCallsSMap(interestedValues);
        mapStatementToVariable(synonymValues, relationship);
    }
}

void mapStatementToVariable(StringVector &synonymValues,
                            std::unordered_map<int, std::unordered_set<std::string>> &relationship) {
    for (auto &value : synonymValues) {
        auto it = relationship.find(stoi(value));
        value = *(it->second.begin());
    }
}
