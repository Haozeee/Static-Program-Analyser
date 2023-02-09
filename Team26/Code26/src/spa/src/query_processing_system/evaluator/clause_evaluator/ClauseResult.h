#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "../Result.h"

class ClauseResult : public Result {
 private:
    /**
     * Indicates if the clause has any results.
     */
    bool noResults = false;

 public:
    void setNoResults();

    bool hasNoResults();
};
