#pragma once
#include <memory>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class ParentManager : public RelationshipManager<int, int> {
 public:
    bool insertRelationship(int first_param, int second_param,
                            std::shared_ptr<WriteOnlyRelationshipManger<int, int>> parentTManager) {
        bool flag = RelationshipManager::insertRelationship(first_param, second_param);
        // duplicate insert into ParentsTManager
        bool flag1 = parentTManager->insertRelationship(first_param, second_param);
        return flag && flag1;
    }
};
