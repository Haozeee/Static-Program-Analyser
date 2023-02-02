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
    bool isEmpty();
    bool contains(Entity, Relationship);
    std::unordered_map<Entity, Relationship> getAllRelationships();
};



