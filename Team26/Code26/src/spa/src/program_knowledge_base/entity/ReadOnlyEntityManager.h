#pragma once

#include <unordered_set>

template<typename Entity>
class ReadOnlyEntityManager {
 public:
    virtual bool isEmpty() = 0;
    virtual bool contains(Entity) = 0;
    virtual std::unordered_set<Entity> getAllEntitiesEntries() = 0;
};
