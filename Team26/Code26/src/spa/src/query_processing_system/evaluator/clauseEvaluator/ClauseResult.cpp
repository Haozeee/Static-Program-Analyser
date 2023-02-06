#include "ClauseResult.h"

void ClauseResult::addNewItem(std::string key, std::unordered_set<std::string> values) {
    results.insert({key, values});
}

ResultMap ClauseResult::getResults() {
    return results;
}

bool ClauseResult::hasNoResults() {
    return noResults;
}

void ClauseResult::setNoResults() {
    noResults = true;
}
