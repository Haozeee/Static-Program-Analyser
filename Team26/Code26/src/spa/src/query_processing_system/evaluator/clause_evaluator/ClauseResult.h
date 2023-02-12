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

    /**
     * Checks if all keys in the results are mapped to empty values.
     * @return Returns true if there are keys in the results but no values.
     */
    bool keysHasNoValues();
};
