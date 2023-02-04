#pragma once
#include <unordered_set>
#include "WriteOnlyEntityManager.h"
#include "ReadOnlyEntityManager.h"

template <typename Entity>
class EntityManager : public WriteOnlyEntityManager<Entity> , public ReadOnlyEntityManager<Entity> {
 private :
    std::unordered_set<Entity> entities_set;
public:
    bool insertEntity(Entity entity) {
        bool flag = entities_set.insert(entity).second;
        return flag;
    }

    bool isEmpty() {
        bool flag = true;
        if (entities_set.size() != 0) {
            flag = false;
        }
        return flag;
    }

    bool contains(Entity entity) {
        auto element = entities_set.find(entity);
        return element != entities_set.end();
    }

    std::unordered_set<Entity> getAllEntitiesEntries() {
        return entities_set;
    }
};
