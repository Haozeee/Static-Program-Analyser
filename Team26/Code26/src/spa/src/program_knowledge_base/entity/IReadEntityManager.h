#pragma once

#include <unordered_set>

template<typename T>
class IReadEntityManager {
 public:
    virtual bool isEmpty() = 0;
    virtual bool contains(T entity) = 0;
    virtual std::unordered_set<T> getAllEntitiesEntries() = 0;
};
