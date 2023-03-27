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
    bool isEmptyMap() override {
        return relationshipsMap.empty();
    }

    bool isEmptyReversedMap() override {
        return reversedRelationshipsMap.empty();
    }

    bool containsMap(T firstParam, U secondParam) override {
        auto key = relationshipsMap.find(firstParam);
        if (key != relationshipsMap.end()) {
            auto res = key->second;
            return res.count(secondParam);
        } else {
            return false;
        }
    }

    bool containsReversedMap(U secondParam, T firstParam) override {
        auto key = reversedRelationshipsMap.find(secondParam);
        if (key != reversedRelationshipsMap.end()) {
            auto res = key->second;
            return res.count(firstParam);
        } else {
            return false;
        }
    }

    std::unordered_map<T, std::unordered_set<U>> getAllRelationshipEntries() override {
        return relationshipsMap;
    }

    std::unordered_map<U, std::unordered_set<T>> getAllReversedRelationshipEntries() override {
        return reversedRelationshipsMap;
    }

    bool insertRelationship(T firstParam, U secondParam) override {
        if (!relationshipsMap.count(firstParam)) {
            std::unordered_set<U> newSet;
            newSet.insert(secondParam);
            auto res = relationshipsMap.emplace(firstParam, newSet);
            return res.second;
        } else {
            auto res = relationshipsMap[firstParam].insert(secondParam);
            return res.second;
        }
    }

    void setReverse() override {
        for (auto pair : relationshipsMap) {
            auto key = pair.first;
            auto value = pair.second;
            for (auto element : value) {
                setReverseHelper(key, element);
            }
        }
    }

 private:
    void setReverseHelper(T key, U element) {
        if (!reversedRelationshipsMap.count(element)) {
            std::unordered_set<T> newSet;
            newSet.insert(key);
            reversedRelationshipsMap.emplace(element, newSet);
        } else {
            reversedRelationshipsMap[element].insert(key);
        }
    }
};
