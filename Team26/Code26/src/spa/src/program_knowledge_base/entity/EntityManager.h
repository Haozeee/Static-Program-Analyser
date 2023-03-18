#pragma once

#include <unordered_set>
#include "IWriteEntityManager.h"
#include "IReadEntityManager.h"

template <typename T>
class EntityManager : public IWriteEntityManager<T>,
        public IReadEntityManager<T> {
 private:
    std::unordered_set<T> entitiesSet;

 public:
    bool insertEntity(T nameOrStmtNo) {
        auto insertedEntity =  entitiesSet.insert(nameOrStmtNo);
        bool flag = insertedEntity.second;
        return flag;
    }

    bool isEmpty() {
        bool flag = true;
        if (entitiesSet.size() != 0) {
            flag = false;
        }
        return flag;
    }

    bool contains(T nameOrStmtNo) {
        bool flag = false;
        auto element = entitiesSet.find(nameOrStmtNo);
        if (element != entitiesSet.end()) {
            flag = true;
        }
        return flag;
    }

    std::unordered_set<T> getAllEntitiesEntries() {
        return entitiesSet;
    }
};
