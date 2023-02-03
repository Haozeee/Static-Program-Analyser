#include "RelationshipManager.h"
#include <unordered_map>

template <typename Entity, typename Relationship>
bool RelationshipManager<Entity, Relationship>::isEmpty() {
    return relationships_map.empty();
}

template <typename Entity, typename Relationship>
bool RelationshipManager<Entity, Relationship>::contains(Entity entity, Relationship relationship) {
    if (relationships_map.contains(entity)) {
        auto keyValuePair = relationships_map.find(entity);
        return keyValuePair->relationship == relationship;
    }
    return false;
}

template <typename Entity, typename Relationship>
std::unordered_map<Entity, Relationship> RelationshipManager<Entity, Relationship>::getAllRelationshipEntries() {
    return relationships_map;
}
