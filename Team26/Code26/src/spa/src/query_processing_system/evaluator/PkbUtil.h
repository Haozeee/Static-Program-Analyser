#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <utility>
#include "../parser/DesignEntity.h"
#include "../../program_knowledge_base/StorageManager.h"

using stringEntitySet = std::unordered_set<std::string>;

class PkbUtil {
 public:
    static std::unordered_set<std::string> getStringEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                                    DesignEntity entity);

    static std::unordered_set<int> getIntEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                         DesignEntity entity);

    static std::unordered_set<std::string> getEntitiesFromPkb(std::shared_ptr<ReadStorage> storage,
                                                              DesignEntity entity);
};
