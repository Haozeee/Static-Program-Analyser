#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <utility>
#include "../parser/DesignEntity.h"
#include "../../program_knowledge_base/StorageManager.h"

using stringEntitySet = std::unordered_set<std::string>;

class PkbUtil {
 public:
    static std::unordered_set<std::string> getStringEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                                    DesignEntity entity);

    static std::unordered_set<int> getIntEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                         DesignEntity entity);

    static std::unordered_set<std::string> getEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                              DesignEntity entity);

    /**
    * Converts a set containing integers to a set of strings.
    * @param intSet The set to be converted.
    * @return The string set.
    */
    static std::unordered_set<std::string> intSetToStringSet(std::unordered_set<int> intSet);

    /**
     * Takes in a map containing integer keys and integers sets as values and
     * converts all the integer values to strings.
     * @param intMap The map to be converted.
     * @return The converted string map.
     */
    static std::unordered_map<std::string, std::unordered_set<std::string>> intMapTostringMap(
            std::unordered_map<int, std::unordered_set<int>> intMap);

    /**
     * Given two sets containing elements of type T, get the intersection of the two sets.
     * @parsm res The set to store the intersection in.
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
     * Given a map<T, set<U>> and a set of search keys of type T,
     * return the map containing only the keys found in the search keys along with their corresponding values.
     * @tparam T The type of the keys of the map.
     * @tparam U The type of the set elements of the value.
     * @param map The map to search from.
     * @param filterKeys The list of keys to search.
     * @return The union of all the values of the search keys.
     */
    template<typename T, typename U>
    static std::unordered_map<T, std::unordered_set<U>> filterMap(
            std::unordered_map<T, std::unordered_set<U>> map, std::unordered_set<T> filterKeys) {
        std::unordered_map<T, std::unordered_set<U>> res;
        for (T key : filterKeys) {
            auto it = map.find(key);
            if (it != map.end()) {
                res.insert({key, it->second});
            }
        }
        return res;
    }

    /**
     * Find the intersection between a Map of type <T, Set<U>> with a set of type <U>.
     * Given a map with keys k and values v and a set S, this function filters the values v
     * such that they only contain values in S.
     * @tparam T The type of the keys of the map.
     * @tparam U The type of the set.
     */
    template<typename T, typename U>
    static std::unordered_map<T, std::unordered_set<U>> mapSetIntersection(
            std::unordered_map<T, std::unordered_set<U>> map, std::unordered_set<U> set) {
        std::unordered_map<T, std::unordered_set<U>> res;
        if (set.empty()) {
            return res;
        }
        for (auto const& [k, v] : map) {
            std::unordered_set<U> intersection;
            PkbUtil::setIntersection(v, set, intersection);
            if (!intersection.empty()) {
                res.insert({k, intersection});
            }
        }
        return res;
    }
};
