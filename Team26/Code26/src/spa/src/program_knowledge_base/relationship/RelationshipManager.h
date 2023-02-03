#pragma once

#include <unordered_map>
#include "ReadOnlyRelationshipManager.h"
#include "WriteOnlyRelationshipManager.h"

template <typename T, typename U>
class RelationshipManager: public ReadOnlyRelationshipManager<T, U>,
        public WriteOnlyRelationshipManger<T, U> {
 private:
    std::unordered_map<T, U> relationships;
 public:
    bool isEmpty();
    bool contains(T, U);
    std::unordered_map<T, U> getAllRelationships();
};



