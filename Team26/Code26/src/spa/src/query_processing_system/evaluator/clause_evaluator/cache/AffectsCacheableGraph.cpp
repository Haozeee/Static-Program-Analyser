#include "AffectsCacheableGraph.h"
#include <stack>

AffectsCacheableGraph::AffectsCacheableGraph(StoragePointer storage) : AffectsBaseCacheableGraph(storage) {}

void AffectsCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllRelationshipEntries();
}

void AffectsCacheableGraph::onCacheMiss(int startStatement) {
    if (!assignStatements.count(startStatement) || !base.count(startStatement)) {
        // Not an assign statement
        return;
    }

    std::string variableModified = modifiesVariable(startStatement);

    std::unordered_set<int> visited;
    std::unordered_set<int> results;
    std::stack<int> stack;
    std::string nodeVariable;

    int node = startStatement;
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
            if (assignStatements.count(neighbour)) {
                if (usesMap.count(neighbour) && usesMap.at(neighbour).count(variableModified)) {
                    results.insert(neighbour);
                }
            }
            if (isReadCallOrAssign(neighbour)) {
                nodeVariable = modifiesVariable(neighbour);
                if (variableModified == nodeVariable) {
                    continue;
                }
            }

            if (!visited.count(neighbour)) {
                stack.push(neighbour);
            }
        }
    }

    cache.insert({startStatement, results});
}
