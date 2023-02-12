#include "ClauseResult.h"

bool ClauseResult::hasNoResults() {
    return noResults;
}

void ClauseResult::setNoResults() {
    noResults = true;
}

bool ClauseResult::keysHasNoValues() {
    if (results.empty()) {
        return true;
    }
    for (auto const& [k, v] : results) {
        if (!v.empty()) {
            return false;
        }
    }
    return true;
}
