#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "ReadOnlyRelationshipManager.h"
#include "WriteOnlyRelationshipManager.h"

template <typename T, typename U>
class RelationshipManager: public ReadOnlyRelationshipManager<T, U>,
                           public WriteOnlyRelationshipManger<T, U> {
 protected:
    std::unordered_map<T, std::unordered_set<U>> relationships_map;
    std::unordered_map<U, std::unordered_set<T>> reversed_relationships_map;
 public:
    bool isEmptyMap() {
        return relationships_map.empty();
    }

    bool isEmptyReversedMap() {
        return reversed_relationships_map.empty();
    }

    bool containsMap(T first_param, U second_param) {
        auto key = relationships_map.find(first_param);
        if (key != relationships_map.end()) {
            auto res = key->second;
            return res.count(second_param);
        }
        return false;
    }

    bool containsReversedMap(U second_param, T first_param) {
        auto key = reversed_relationships_map.find(second_param);
        if (key != reversed_relationships_map.end()) {
            auto res = key->second;
            return res.count(first_param);
        }
        return false;
    }

    std::unordered_map<T, std::unordered_set<U>> getAllRelationshipEntries() {
        return relationships_map;
    }
    std::unordered_map<U, std::unordered_set<T>> getAllReversedRelationshipEntries() {
        return reversed_relationships_map;
    }

    bool insertRelationship(T first_param, U second_param) {
        // std::cout << "NON-Override " << first_param << " " << second_param << "\n";
        bool flag = false;
        bool flag1 = false;
        // the key is not a key in the map
        if (!relationships_map.count(first_param)) {
            std::unordered_set<U> new_set;
            new_set.insert(second_param);
            auto res = relationships_map.emplace(first_param, new_set);
            flag = res.second;
        } else {
            auto res = relationships_map[first_param].insert(second_param);
            flag = res.second;
        }

        if (!reversed_relationships_map.count(second_param)) {
            std::unordered_set<T> new_set;
            new_set.insert(first_param);
            auto res = reversed_relationships_map.emplace(second_param, new_set);
            flag1 = res.second;
        } else {
            auto res = reversed_relationships_map[second_param].insert(first_param);
            flag1 = res.second;
        }
        return flag && flag1;
    }

    bool insertRelationship(T first_param, U second_param,
                            std::shared_ptr<WriteOnlyRelationshipManger<T, U>> manager) {
        return false;
    }
};
