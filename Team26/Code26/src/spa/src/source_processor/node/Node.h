#pragma once

// Abstract base class
class Node {
 public:
    virtual ~Node() = default;
    virtual bool operator==(const Node& node) const = 0; 
};
