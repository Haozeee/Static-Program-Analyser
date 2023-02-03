#pragma once

#include <unordered_map>

template <typename Entity, typename Relationship>
class ReadOnlyRelationshipManager {
 public:
    virtual bool isEmpty() = 0;
    virtual bool contains(Entity, Relationship) = 0;
    virtual std::unordered_map<Entity, Relationship> getAllRelationshipEntries() = 0;
};
