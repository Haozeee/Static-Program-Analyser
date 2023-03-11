#pragma once
#include <memory>

template<typename T>
class SharedPointerComparator {
 public:
    bool operator()(const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) const {
        return *a == *b;
    }
};
