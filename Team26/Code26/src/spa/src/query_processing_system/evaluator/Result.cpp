#include "Result.h"
#include "PkbUtil.h"

void Result::addNewResult(std::string key, std::unordered_set<std::string> toAdd) {
    auto it = results.find(key);
    if (it != results.end()) {
        it->second = toAdd;
    } else {
        results.insert({key, toAdd});
    }
}

void Result::unionResult(std::string key, std::unordered_set<std::string> toUnion) {
    auto it = results.find(key);
    if (it != results.end()) {
        PkbUtil::setUnion(it->second, toUnion);
    } else {
        results.insert({key, toUnion});
    }
}

ResultMap Result::getResults() {
    return results;
}

std::ostream& operator <<(std::ostream& os, const Result& result) {
    os << "Displaying Result: \n";
    for (auto i : result.results) {
        os << "Identity: " << i.first << "\n";
        os << "Results: ";
        for (auto j : i.second) {
            os << j << " ";
        }
        os << "\n";
    }
    return os;
}
