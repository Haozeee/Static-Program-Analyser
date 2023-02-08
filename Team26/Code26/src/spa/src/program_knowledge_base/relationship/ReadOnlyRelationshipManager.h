#pragma once

#include <unordered_map>
#include <unordered_set>

template <typename T, typename U>
class ReadOnlyRelationshipManager {
 public:
    virtual bool isEmpty() = 0;
    virtual bool contains(T, U) = 0;
    virtual std::unordered_map<T, std::unordered_set<U>> getAllRelationshipEntries() = 0;
    virtual std::unordered_map<U, std::unordered_set<T>> getAllReversedRelationshipEntries() = 0;
};
