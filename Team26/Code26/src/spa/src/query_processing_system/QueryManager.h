#pragma once
#include <string>

class ReadOnlyStorage;

class QueryManager {
 public:
    void process(const std::string& query);
};
