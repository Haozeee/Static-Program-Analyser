#pragma once
#include <string>
#include <memory>
#include <utility>

class ShuntNode;

class ShuntNode {
 public:
    const std::string value;
    std::shared_ptr<ShuntNode> left;
    std::shared_ptr<ShuntNode> right;
    explicit ShuntNode(std::string value) : value(std::move(value)), left(nullptr), right(nullptr) {}
};
