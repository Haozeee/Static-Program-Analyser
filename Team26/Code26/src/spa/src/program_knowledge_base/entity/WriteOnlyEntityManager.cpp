#include "WriteOnlyEntityManager.h"

// this is an interface

template<typename Entity>
bool WriteOnlyEntityManager<Entity>::insertEntity(Entity entity) {
    return false;
}