#include "TransitiveCacheableGraph.h"
#include <stack>

TransitiveCacheableGraph::TransitiveCacheableGraph(StoragePointer storage) : CacheableGraph<int, int>(storage) {}

void TransitiveCacheableGraph::onCacheMiss(int startNode) {
    if (!base.count(startNode)) {
        return;
    }

    std::unordered_set<int> visited;
    std::unordered_set<int> reachable;
    std::stack<int> stack;

    int node = startNode;
    stack.push(node);

    while (!stack.empty()) {
        node = stack.top();
        stack.pop();

        if (visited.count(node)) {
            continue;
        }

        visited.insert(node);
        std::unordered_set<int> neighbours;
        if (base.count(node)) {
            neighbours = base.at(node);
        }
        for (auto neighbour : neighbours) {
            reachable.insert(neighbour);
            if (!visited.count(neighbour)) {
                stack.push(neighbour);
            }
        }
    }

    cache.insert({startNode, reachable});
}
