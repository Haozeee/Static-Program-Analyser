#pragma once
#include <memory>
#include "ResultTable.h"
class QueryDb {
 private:
    std::vector<std::shared_ptr<ResultTable>> results;

 public:
    QueryDb();

    void addResult(std::shared_ptr<ResultTable> toAdd);
};
