#pragma once

template <typename T, typename U>
class WriteOnlyRelationshipManger {
 public:
    virtual bool insertRelationship(T entity, U relationship) = 0;
};
