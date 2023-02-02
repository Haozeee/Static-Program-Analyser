#pragma once
#include <unordered_set>
#include "WriteOnlyEntityManager.h"
#include "ReadOnlyEntityManager.h"

template <typename Entity>

class EntityManager : WriteOnlyEntityManager<Entity> , ReadOnlyEntityManager<Entity> {
    private :
        std::unordered_set<Entity> entities_set;
    public:
        bool insertEntity(Entity entity);

        std::unordered_set<Entity> getAllEntitiesEntries();

        bool isEmpty();
};