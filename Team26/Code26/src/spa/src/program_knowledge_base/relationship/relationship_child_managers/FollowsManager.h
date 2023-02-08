#pragma once
#include <memory>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class FollowsManager : public RelationshipManager<int, int> {
 public:
    bool insertRelationship(int first_param, int second_param,
                            std::shared_ptr<WriteOnlyRelationshipManger<int, int>> followsTManager) {
        bool flag = RelationshipManager::insertRelationship(first_param, second_param);
        // duplicate insert into FollowsTManager
        bool flag1 = followsTManager->insertRelationship(first_param, second_param);
        return flag && flag1;
    }
};
