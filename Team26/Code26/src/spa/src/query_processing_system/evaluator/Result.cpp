#include "Result.h"

void Result::addNewResult(std::string key, std::unordered_set<std::string> toAdd) {
    auto it = results.find(key);
    if (it != results.end()) {
        it->second = toAdd;
    }
}

ResultMap Result::getResults() {
    return results;
}
