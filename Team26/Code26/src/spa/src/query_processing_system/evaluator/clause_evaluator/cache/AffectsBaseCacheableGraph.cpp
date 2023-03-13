#include "AffectsBaseCacheableGraph.h"
#include <stack>

AffectsBaseCacheableGraph::AffectsBaseCacheableGraph(StoragePointer storage) : CacheableGraph<int, int>(storage) {
    modifiesMap = storage->getModifiesSManager()->getAllRelationshipEntries();
    assignStatements = storage->getAssignManager()->getAllEntitiesEntries();
    readStatements = storage->getReadStmtNoManager()->getAllEntitiesEntries();
    callStatements = storage->getCallStmtNoManager()->getAllEntitiesEntries();
}

bool AffectsBaseCacheableGraph::isReadCallOrAssign(int stmt) {
    return assignStatements.count(stmt) || readStatements.count(stmt) || callStatements.count(stmt);
}

std::string AffectsBaseCacheableGraph::modifiesVariable(int stmt) {
    return *(modifiesMap.at(stmt).begin());
}

void AffectsBaseCacheableGraph::onCacheMiss(int startStatement) {
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
            if (isReadCallOrAssign(neighbour)) {
                nodeVariable = modifiesVariable(neighbour);
                if (variableModified == nodeVariable) {
                    results.insert(neighbour);
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

void AffectsBaseCacheableGraph::buildAll() {
    std::unordered_set<int> currentItems = Util::getAllKeys(cache);
    std::unordered_set<int> missingItems = {};
    insertItemsIntoCache(missingItems);
}
