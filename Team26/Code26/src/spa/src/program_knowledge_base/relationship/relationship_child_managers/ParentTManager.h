#pragma once
#include "program_knowledge_base/relationship/RelationshipManager.h"

class ParentTManager : public RelationshipManager<int, int> {
 public:
    bool insertRelationship(int first, int second) override{
        // TODO: (ZH) Remove added temporary fix for transitive
        bool flag = RelationshipManager::insertRelationship(first, second);
        if (!reversed_relationships_map.count(second)) {
            std::unordered_set<int> new_set;
            new_set.insert(first);
            auto res = reversed_relationships_map.emplace(second, new_set);
        } else {
            auto res = reversed_relationships_map[second].insert(first);
        }
        if (relationships_map.count(second)) {
            auto res = relationships_map[second];
            for (auto itr : res) {
                flag = flag && RelationshipManager::insertRelationship(first, itr);
                if (!reversed_relationships_map.count(itr)) {
                    std::unordered_set<int> new_set;
                    new_set.insert(first);
                    auto res = reversed_relationships_map.emplace(itr, new_set);
                } else {
                    auto res = reversed_relationships_map[itr].insert(first);
                }
            }
        } else {
            if (reversed_relationships_map.count(first)) {
                auto res = reversed_relationships_map[first];
                for (auto itr : res) {
                    flag = flag && RelationshipManager::insertRelationship(itr, second);
                    if (!reversed_relationships_map.count(itr)) {
                        std::unordered_set<int> new_set;
                        new_set.insert(first);
                        auto res = reversed_relationships_map.emplace(itr, new_set);
                    } else {
                        auto res = reversed_relationships_map[itr].insert(first);
                    }
                }
            }
        }
        return flag;
    }
};
