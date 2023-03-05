#pragma once
#include <memory>
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsManager : public RelationshipManager<std::string, std::string> {
 public:
    bool insertRelationship(std::string first_param, std::string second_param,
                            std::shared_ptr<IWriteRelationshipManager<std::string, std::string>> callsTManager) {
        bool flag = RelationshipManager::insertRelationship(first_param, second_param);
        // duplicate insert into callsTManager
        bool flag1 = callsTManager->insertRelationship(first_param, second_param);
        return flag && flag1;
    }
};

