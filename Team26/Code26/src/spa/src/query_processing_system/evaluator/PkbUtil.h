#pragma once
#include <memory>
#include "../parser/DesignEntity.h"
#include "../../program_knowledge_base/ReadOnlyStorage.h"

using ResultSet = std::unordered_set<std::string>;

class PkbUtil {
public:
    static ResultSet getEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity);

    static ResultSet setIntersection(ResultSet setA, ResultSet setB);

    /**
    * Converts a set containing integers to a set of strings.
    * @param intSet The set to be converted.
    * @return The string set.
    */
    static std::unordered_set<std::string> intSetToStringSet(std::unordered_set<int> intSet);
};
