#include "ShuntNode.h"

std::string ShuntNode::getPreOrderTraversal(std::shared_ptr<ShuntNode> node) {
    if (node == nullptr) {
        return "";
    }
    std::string s = node->value;
    s += getPreOrderTraversal(node->left);
    s += getPreOrderTraversal(node->right);
    return s;
}

std::string ShuntNode::getInOrderTraversal(std::shared_ptr<ShuntNode> node) {
    if (node == nullptr) {
        return "";
    }
    std:: string s = getInOrderTraversal(node->left);
    s += node->value;
    s += getInOrderTraversal(node->right);
    return s;
}

bool ShuntNode::isSubTree(const std::shared_ptr<ShuntNode>& fullTree, const std::shared_ptr<ShuntNode>& partialTree) {
    /**
     * Given 2 trees A and B. Tree B is a subtree of A if the pre-order
     * traversal of B is a substring of the pre-order traversal of A AND
     * the in-order traversal of B is a substring of the in-order traversal of A.
     * The runtime is O(n).
     */
    if (partialTree == nullptr) {
        return true;
    }
    if (fullTree == nullptr) {
        return false;
    }
    std::string inOrder = getInOrderTraversal(fullTree);
    std::string preOrder = getPreOrderTraversal(fullTree);
    std::string partialInOrder = getInOrderTraversal(partialTree);
    std::string partialPreOrder = getPreOrderTraversal(partialTree);
    bool inOrderSubstring = inOrder.find(partialInOrder) != std::string ::npos;
    bool preOrderSubstring = preOrder.find(partialPreOrder) != std::string ::npos;
    return inOrderSubstring && preOrderSubstring;
}
