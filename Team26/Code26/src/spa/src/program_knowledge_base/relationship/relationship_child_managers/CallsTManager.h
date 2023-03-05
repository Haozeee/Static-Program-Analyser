#pragma once
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsTManager : public RelationshipManager<std::string, std::string> {
 public:
    bool insertRelationship(std::string first, std::string second){
        bool flag = RelationshipManager::insertRelationship(first, second);
        if (reversed_relationships_map.count(first)) {
            auto res = reversed_relationships_map[first];
            for (auto itr : res) {
                flag = flag && RelationshipManager::insertRelationship(itr, second);
            }
        }
        return flag;
    }
};
