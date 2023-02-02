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
std::unordered_set<Entity> EntityManager<Entity>::getAllEntitiesEntries() {
    return entities_set;
}

template<typename Entity>
bool EntityManager<Entity>::isEmpty() {
    bool flag = true;
    if (entities_set.size() != 0) {
        flag = false;
    }
    return flag;
}