#include "WriteOnlyRelationshipManager.h"

// this is an interface

template<typename Entity, typename Relationship>
bool WriteOnlyRelationshipManger<Entity, Relationship>::insertRelationship(Entity entity, Relationship relationship) {
    return false;
}
