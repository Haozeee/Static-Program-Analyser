#pragma once

#include <unordered_map>

template <typename T, typename U>
class ReadOnlyRelationshipManager {
 public:
    virtual bool isEmpty() = 0;
    virtual bool contains(T, U) = 0;
    virtual std::unordered_map<T, U> getAllRelationshipEntries() = 0;
};
