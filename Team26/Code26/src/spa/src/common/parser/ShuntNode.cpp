#include "ShuntNode.h"
#include "ShuntingYardParser.h"

std::vector<std::string> ShuntNode::getPreOrderTraversal(std::shared_ptr<ShuntNode> node) {
    std::vector<std::string> res;
    if (node == nullptr) {
        return res;
    }
    res.push_back(node->value);
    auto left = getPreOrderTraversal(node->left);
    res.insert(res.end(), left.begin(), left.end());
    auto right = getPreOrderTraversal(node->right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

std::vector<std::string> ShuntNode::getInOrderTraversal(std::shared_ptr<ShuntNode> node) {
    std::vector<std::string> res;
    if (node == nullptr) {
        return res;
    }
    auto left = getInOrderTraversal(node->left);
    res.insert(res.end(), left.begin(), left.end());
    res.push_back(node->value);
    auto right = getInOrderTraversal(node->right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

bool ShuntNode::isSubVector(std::vector<std::string> stringVector, std::vector<std::string> subVector) {
    int i = 0;
    int j = 0;
    while (i < stringVector.size() && j < subVector.size()) {
        if (stringVector[i] == subVector[j]) {
            j++;
        } else {
            j = 0;
            if (stringVector[i] == subVector[j]) {
                j++;
            }
        }
        i++;
    }
    return j == subVector.size();
}

bool ShuntNode::stringsProducesEqualTrees(std::string stringA, std::string stringB) {
    auto a = ShuntingYardParser::parse(stringA);
    auto b = ShuntingYardParser::parse(stringB);
    auto aInOrder = ShuntNode::getInOrderTraversal(a);
    auto aPreOrder = ShuntNode::getPreOrderTraversal(a);
    auto bInOrder = ShuntNode::getInOrderTraversal(b);
    auto bPreOrder = ShuntNode::getPreOrderTraversal(b);
    return aInOrder == bInOrder && aPreOrder == bPreOrder;
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
    std::vector<std::string> inOrder = getInOrderTraversal(fullTree);
    std::vector<std::string> preOrder = getPreOrderTraversal(fullTree);
    std::vector<std::string> partialInOrder = getInOrderTraversal(partialTree);
    std::vector<std::string> partialPreOrder = getPreOrderTraversal(partialTree);
    bool inOrderSubstring = isSubVector(inOrder, partialInOrder);
    bool preOrderSubstring = isSubVector(preOrder, partialPreOrder);
    return inOrderSubstring && preOrderSubstring;
}
