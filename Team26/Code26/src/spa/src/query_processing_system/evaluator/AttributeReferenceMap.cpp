#include "AttributeReferenceMap.h"

void mapAttribute(const AttributeReference& attributeRef, StringVector &synonymValues,
                  std::shared_ptr<ReadStorage> storage) {
    std::unordered_map<int, std::unordered_set<std::string>> relationship;
    if (attributeRef.getDesignEntity() == DesignEntity::READ && attributeRef.getAttributeName() == varName) {
        relationship = StorageUtil::getRelationshipMap(storage->getModifiesSManager());
        mapStatementToVariable(synonymValues, relationship);
    } else if (attributeRef.getDesignEntity() == DesignEntity::PRINT && attributeRef.getAttributeName() == varName) {
        relationship = StorageUtil::getRelationshipMap(storage->getUsesSManager());
        mapStatementToVariable(synonymValues, relationship);
    } else if (attributeRef.getDesignEntity() == DesignEntity::CALL && attributeRef.getAttributeName() == procName) {
        relationship = StorageUtil::getRelationshipMap(storage->getCallsSManager());
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
