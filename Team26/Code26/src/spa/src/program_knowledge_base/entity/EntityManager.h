#pragma once
#include <unordered_set>
#include "IWriteEntityManager.h"
#include "IReadEntityManager.h"

template <typename T>
class EntityManager : public IWriteEntityManager<T>,
        public IReadEntityManager<T> {
 private:
    std::unordered_set<T> entities_set;

 public:
    bool insertEntity(T name_or_stmtNo) {
        bool flag = entities_set.insert(name_or_stmtNo).second;
        return flag;
    }

    bool isEmpty() {
        bool flag = true;
        if (entities_set.size() != 0) {
            flag = false;
        }
        return flag;
    }

    bool contains(T name_or_stmtNo) {
        auto element = entities_set.find(name_or_stmtNo);
        return element != entities_set.end();
    }

    std::unordered_set<T> getAllEntitiesEntries() {
        return entities_set;
    }
};
