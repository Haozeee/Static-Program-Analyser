#pragma once
#include <memory>

template <typename T, typename U>
class IWriteRelationshipManager {
 public:
    virtual bool insertRelationship(T first_param, U second_param) = 0;
    virtual void setReverse() = 0;
};
