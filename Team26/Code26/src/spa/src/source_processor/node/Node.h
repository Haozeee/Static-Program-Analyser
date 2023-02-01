#pragma once

#include <string>
#include <variant>

using factor = std::variant<std::string, int>;

// Abstract base class
class Node {
 public:
    virtual ~Node() = default;
    virtual bool operator==(const Node& node) const = 0; 
};
