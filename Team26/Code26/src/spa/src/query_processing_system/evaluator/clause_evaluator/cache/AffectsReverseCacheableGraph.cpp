#include "AffectsReverseCacheableGraph.h"
#include <stack>

AffectsReverseCacheableGraph::AffectsReverseCacheableGraph(StoragePointer storage)
    : AffectsBaseCacheableGraph(storage) {}

void AffectsReverseCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllReversedRelationshipEntries();
}

void AffectsReverseCacheableGraph::onCacheMiss(int startStatement) {
    if (!assignStatements.count(startStatement) || !base.count(startStatement)) {
        // Not an assign statement
        return;
    }

    std::unordered_set<std::string> variablesUsed;
    if (usesMap.count(startStatement)) {
        variablesUsed = usesMap.at(startStatement);
        if (variablesUsed.empty()) {
            return;
        }
    }

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
                if (variablesUsed.count(modifiesVariable(neighbour))) {
                    results.insert(neighbour);
                    continue;
                }
            }
            if (isReadCallOrAssign(neighbour)) {
                nodeVariable = modifiesVariable(neighbour);
                if (variablesUsed.count(nodeVariable)) {
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
