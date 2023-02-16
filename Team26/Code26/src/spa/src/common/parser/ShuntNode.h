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

    static std::string getInOrderTraversal(std::shared_ptr<ShuntNode> node);

    static std::string getPreOrderTraversal(std::shared_ptr<ShuntNode> node);

    /**
     * Given another node, check if the tree rooted at that node is a subtree of the current tree.
     * @return True, if it is a sub tree. Otherwise, false.
     */
    static bool isSubTree(const std::shared_ptr<ShuntNode>& fullTree, const std::shared_ptr<ShuntNode>& partialTree);
};
