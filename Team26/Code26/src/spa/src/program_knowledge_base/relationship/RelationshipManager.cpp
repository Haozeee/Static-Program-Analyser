#include "RelationshipManager.h"
#include <unordered_map>

template <typename T, typename U>
bool RelationshipManager<T, U>::isEmpty() {
    return relationships.empty();
}

template <typename T, typename U>
bool RelationshipManager<T, U>::contains(T first, U second) {
    if (relationships.contains(first)) {
        auto keyValuePair = relationships.find(first);
        return keyValuePair->second == second;
    }
    return false;
}

template <typename T, typename U>
std::unordered_map<T, U> RelationshipManager<T, U>::getAllRelationships() {
    return relationships;
}
