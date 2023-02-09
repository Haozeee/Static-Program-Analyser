#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include "../parser/DesignEntity.h"
#include "../../program_knowledge_base/ReadOnlyStorage.h"

using stringEntitySet = std::unordered_set<std::string>;
using intEntitySet = std::unordered_set<int>;

class PkbUtil {
 public:
    static stringEntitySet getEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity);

    /**
     * Get all entities that are of statement form from the pkb.
     */
    static intEntitySet getStatementEntitiesFromPkb(std::shared_ptr<ReadOnlyStorage> storage, DesignEntity entity);

    /**
    * Converts a set containing integers to a set of strings.
    * @param intSet The set to be converted.
    * @return The string set.
    */
    static std::unordered_set<std::string> intSetToStringSet(std::unordered_set<int> intSet);

    /**
     * Given two sets containing elements of type T, get the intersection of the two sets.
     */
    template<typename T>
    static void setIntersection(const std::unordered_set<T> &setA,
                                const std::unordered_set<T> &setB,
                                std::unordered_set<T> &res) {
        // Unable to use std::set_intersection as the two sets are not in sorted order
        // Iterate over the smaller sized set
        auto smallerSet = setA.size() > setB.size() ? setB : setA;
        auto largerSet = setA.size() > setB.size() ? setA : setB;
        for (auto element : smallerSet) {
            if (largerSet.count(element)) {
                res.insert(element);
            }
        }
    }

    /**
     * Union set A with set B. This modifies the reference to setA.
     */
    template<typename T>
    static void setUnion(std::unordered_set<T> &setA, const std::unordered_set<T> &setB) {
        // Unable to use std::set_union as the two sets are not in sorted order
        for (auto i : setB) {
            setA.insert(i);
        }
    }
    /**
     * Given a map<T, set<U>> and a set of search keys of type T.
     * For each key k, get the corresponding value from the map.
     * The value if of type set<U>.
     * Do this for every search key, and union the value set together.
     * @tparam T The type of the keys of the map.
     * @tparam U The type of the set elements of the value.
     * @param store The map to search from.
     * @param searchKeys The list of keys to search.
     * @return The union of all the values of the search keys.
     */
    template<typename T, typename U>
    static std::unordered_set<U> unionSearchKeyResults(std::unordered_map<T, std::unordered_set<U>> store,
                                                         std::unordered_set<T> searchKeys) {
        std::unordered_set<U> res;
        for (T key : searchKeys) {
            auto it = store.find(key);
            if (it != store.end()) {
                PkbUtil::setUnion(res, it->second);
            }
        }

        return res;
    }
};
