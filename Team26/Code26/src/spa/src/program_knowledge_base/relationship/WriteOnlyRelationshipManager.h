#pragma once

template <typename Entity, typename Relationship>
class WriteOnlyRelationshipManger {
    public:
        virtual bool insertRelationship(Entity entity, Relationship relationship);
};



