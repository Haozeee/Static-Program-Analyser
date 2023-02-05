#pragma once

#include <unordered_map>
#include <utility>
#include "ReadOnlyRelationshipManager.h"
#include "WriteOnlyRelationshipManager.h"

template <typename T, typename U>
class RelationshipManager: public ReadOnlyRelationshipManager<T, U>,
        public WriteOnlyRelationshipManger<T, U> {
 private:
    std::unordered_map<T, U> relationships_map;
 public:
    bool isEmpty() {
        return relationships_map.empty();
    }

    bool contains(T first_param, U second_param) {
        auto key = relationships_map.find(first_param);
        if (key != relationships_map.end()) {
            return key->second == second_param;
        }
        return false;
    }

    std::unordered_map<T, U> getAllRelationshipEntries() {
        return relationships_map;
    }

    // TODO(wei-yutong): complete implementation by including 2 way mapping
    bool insertRelationship(T first_param, U second_param) {
        auto flag = relationships_map.insert(std::make_pair(first_param, second_param));
        return flag.second;
    }
};
