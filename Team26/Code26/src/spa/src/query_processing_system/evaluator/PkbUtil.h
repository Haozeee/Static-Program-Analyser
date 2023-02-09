#pragma once
#include <memory>
#include <unordered_set>
#include <algorithm>
#include <string>
#include "../parser/DesignEntity.h"
#include "../../program_knowledge_base/ReadOnlyStorage.h"

using EntitySet = std::unordered_set<std::string>;

class PkbUtil {
 public:
    static EntitySet getEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity);



    static EntitySet setIntersection(const EntitySet &setA, const EntitySet &setB);

    /**
    * Converts a set containing integers to a set of strings.
    * @param intSet The set to be converted.
    * @return The string set.
    */
    static std::unordered_set<std::string> intSetToStringSet(std::unordered_set<int> intSet);
};
