#pragma once

#include <unordered_map>
#include "ReadOnlyRelationshipManager.h"
#include "WriteOnlyRelationshipManager.h"

template <typename Entity, typename Relationship>
class RelationshipManager: public ReadOnlyRelationshipManager<Entity, Relationship>,
        public WriteOnlyRelationshipManger<Entity, Relationship> {
 private:
    std::unordered_map<Entity, Relationship> relationships_map;
 public:
    bool isEmpty() {
        return relationships_map.empty();
    }

    bool contains(Entity entity, Relationship relationship) {
        auto key = relationships_map.find(entity);
        if (key != relationships_map.end()) {
            return key->second == relationship;
        }
        return false;
    }

    std::unordered_map<Entity, Relationship> getAllRelationshipEntries() {
        return relationships_map;
    }

    bool insertRelationship(Entity entity, Relationship relationship) {
        return true;
    }
};
