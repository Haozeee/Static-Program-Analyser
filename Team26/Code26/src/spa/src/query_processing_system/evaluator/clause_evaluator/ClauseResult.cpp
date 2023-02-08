#include "ClauseResult.h"

bool ClauseResult::hasNoResults() {
    return noResults;
}

void ClauseResult::setNoResults() {
    noResults = true;
}
