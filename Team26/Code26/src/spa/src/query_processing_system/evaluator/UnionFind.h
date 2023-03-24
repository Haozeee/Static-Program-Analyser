#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class UnionFind {
 private:
    // id[i] is the parent of i
    // if id[i] == i, i is the root
    std::unordered_map<std::string, std::string> id;

    // size[i] is the size of the component i belongs to
    std::unordered_map<std::string, int> componentSize;

 public:
    UnionFind();

    void add(std::string itemToAdd);

    std::string find(std::string itemToFind);

    void unionItems(std::string p, std::string q);

    void unionMultipleItems(const std::vector<std::string>& itemsToAdd);
};
