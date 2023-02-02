#include "EntityManager.h"
#include <unordered_set>

template <typename Entity>
std::unordered_set<Entity> entities_set;

template<typename Entity>

bool EntityManager<Entity>::insertEntity(Entity entity) {
    bool flag = entities_set.insert(entity).second;
    return flag;
}

template<typename Entity>
std::unordered_set<Entity> EntityManager<Entity>::getAllEntries() {
    return entities_set;
}
