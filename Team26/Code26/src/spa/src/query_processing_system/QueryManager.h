#pragma once
#include <string>
#include <list>
#include <memory>
#include "../program_knowledge_base/StorageUtil.h"
#include "../program_knowledge_base/StorageManager.h"

class ReadOnlyStorage;

class QueryManager {
 private:
    void addSyntaxError(std::list<std::string>&);

    void addSemanticError(std::list<std::string>&);

 public:
    void process(const std::string& query, std::list<std::string> &results, std::shared_ptr<ReadStorage> storageUtil);
};
