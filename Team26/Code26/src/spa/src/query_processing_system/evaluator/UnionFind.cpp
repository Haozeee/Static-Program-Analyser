#include "UnionFind.h"
#include <utility>

UnionFind::UnionFind() = default;

void UnionFind::add(std::string itemToAdd) {
    if (!id.count(itemToAdd)) {
        id.insert({itemToAdd, itemToAdd});
        componentSize.insert({itemToAdd, 1});
    }
}

std::string UnionFind::find(std::string itemToFind) {
    if (!id.count(itemToFind)) {
        add(itemToFind);
    }

    auto i = itemToFind;
    while (i != id.at(i)) {
        // path compression
        id.at(i) = id.at(id.at(i));
        i = id.at(i);
    }

    return i;
}

void UnionFind::unionItems(std::string p, std::string q) {
    auto i = find(std::move(p));
    auto j = find(std::move(q));
    if (i == j) {
        return;
    }
    // Perform weighted union
    if (componentSize.at(i) < componentSize.at(j)) {
        id.at(i) = j;
        componentSize.at(j) += componentSize.at(i);
    } else {
        id.at(j) = i;
        componentSize.at(i) += componentSize.at(j);
    }
}

void UnionFind::unionMultipleItems(const std::vector<std::string>& itemsToAdd) {
    if (itemsToAdd.empty()) {
        return;
    }

    if (itemsToAdd.size() == 1) {
        find(itemsToAdd.at(0));
        return;
    }

    for (int i = 0; i < itemsToAdd.size() - 1; ++i) {
        unionItems(itemsToAdd.at(i), itemsToAdd.at(i + 1));
    }
}
