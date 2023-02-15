#pragma once

#include <unordered_map>
#include <unordered_set>

template <typename T, typename U>
class IReadRelationshipManager {
 public:
    virtual bool isEmptyMap() = 0;
    virtual bool isEmptyReversedMap() = 0;
    virtual bool containsMap(T, U) = 0;
    virtual bool containsReversedMap(U, T) = 0;
    virtual std::unordered_map<T, std::unordered_set<U>> getAllRelationshipEntries() = 0;
    virtual std::unordered_map<U, std::unordered_set<T>> getAllReversedRelationshipEntries() = 0;
};
