#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "IReadRelationshipManager.h"
#include "IWriteRelationshipManager.h"

template <typename T, typename U>
class RelationshipManager: public IReadRelationshipManager<T, U>,
                           public IWriteRelationshipManager<T, U> {
 protected:
    std::unordered_map<T, std::unordered_set<U>> relationshipsMap;
    std::unordered_map<U, std::unordered_set<T>> reversedRelationshipsMap;
 public:
    bool isEmptyMap() {
        return relationshipsMap.empty();
    }

    bool isEmptyReversedMap() {
        return reversedRelationshipsMap.empty();
    }

    bool containsMap(T firstParam, U secondParam) {
        auto key = relationshipsMap.find(firstParam);
        bool flag = false;
        if (key != relationshipsMap.end()) {
            auto res = key->second;
            flag = res.count(secondParam);
        }
        return flag;
    }

    bool containsReversedMap(U secondParam, T firstParam) {
        auto key = reversedRelationshipsMap.find(secondParam);
        bool flag = false;
        if (key != reversedRelationshipsMap.end()) {
            auto res = key->second;
            flag = res.count(firstParam);
        }
        return flag;
    }

    std::unordered_map<T, std::unordered_set<U>> getAllRelationshipEntries() {
        return relationshipsMap;
    }
    std::unordered_map<U, std::unordered_set<T>> getAllReversedRelationshipEntries() {
        return reversedRelationshipsMap;
    }

    bool insertRelationship(T firstParam, U secondParam) {
        bool flag = false;
        if (!relationshipsMap.count(firstParam)) {
            std::unordered_set<U> newSet;
            newSet.insert(secondParam);
            auto res = relationshipsMap.emplace(firstParam, newSet);
            flag = res.second;
        } else {
            auto res = relationshipsMap[firstParam].insert(secondParam);
            flag = res.second;
        }
        return flag;
    }

    void setReverse() {
        for (auto pair : relationshipsMap) {
            auto key = pair.first;
            auto value = pair.second;
            for (auto element : value) {
                if (!reversedRelationshipsMap.count(element)) {
                    std::unordered_set<T> newSet;
                    newSet.insert(key);
                    auto res = reversedRelationshipsMap.emplace(element, newSet);
                } else {
                    auto res = reversedRelationshipsMap[element].insert(key);
                }
            }
        }
    }
};
