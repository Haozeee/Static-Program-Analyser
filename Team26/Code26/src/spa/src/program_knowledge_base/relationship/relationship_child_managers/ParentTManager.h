#pragma once
#include "program_knowledge_base/relationship/RelationshipManager.h"

class ParentTManager : public RelationshipManager<int, int> {
 public:
    bool insertRelationship(int first, int second) override{
        bool flag = RelationshipManager::insertRelationship(first, second);
        if (relationships_map.count(second)) {
            auto res = relationships_map[second];
            for (auto itr : res) {
                flag = flag && RelationshipManager::insertRelationship(first, itr);
            }
        } else {
            if (reversed_relationships_map.count(first)) {
                auto res = reversed_relationships_map[first];
                for (auto itr : res) {
                    flag = flag && RelationshipManager::insertRelationship(itr, second);
                }
            }
        }
        return flag;
    }
};
