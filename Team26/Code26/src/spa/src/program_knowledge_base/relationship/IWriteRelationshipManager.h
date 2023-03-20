#pragma once
#include <memory>

template <typename T, typename U>
class IWriteRelationshipManager {
 public:
    virtual bool insertRelationship(T firstParam, U secondParam) = 0;
    virtual void setReverse() = 0;
};
