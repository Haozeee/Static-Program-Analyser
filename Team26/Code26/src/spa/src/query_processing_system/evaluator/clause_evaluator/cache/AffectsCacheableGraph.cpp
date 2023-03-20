#include "AffectsCacheableGraph.h"
#include <stack>

AffectsCacheableGraph::AffectsCacheableGraph(StoragePointer storage) : CacheableGraph<int, int>(storage) {
    modifiesMap = storage->getModifiesSManager()->getAllRelationshipEntries();
    usesMap = storage->getUsesSManager()->getAllRelationshipEntries();
    callsSMap = storage->getCallsSManager()->getAllRelationshipEntries();
    assignStatements = storage->getAssignManager()->getAllEntitiesEntries();
    readStatements = storage->getReadStmtNoManager()->getAllEntitiesEntries();
    callStatements = storage->getCallStmtNoManager()->getAllEntitiesEntries();
}


bool AffectsCacheableGraph::isReadOrAssign(int stmt) {
    return assignStatements.count(stmt) || readStatements.count(stmt);
}

std::string AffectsCacheableGraph::modifiesVariable(int stmt) {
    return *(modifiesMap.at(stmt).begin());
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
            if (isReadOrAssign(neighbour) && modifiesMap.count(neighbour)) {
                nodeVariable = modifiesVariable(neighbour);
                if (variableModified == nodeVariable) {
                    continue;
                }
            }
            if (callStatements.count(neighbour)) {
                auto procedureCalled = *(callsSMap.at(neighbour).begin());
                if (storage->getModifiesPManager()->containsMap(procedureCalled, variableModified)) {
                    continue;
                }
            }

            if (!visited.count(neighbour)) {
                stack.push(neighbour);
            }
        }
    }

    cache.insert({startStatement, results});

    for (auto i : results) {
        if (!reverseCache.count(i)) {
            reverseCache.insert({i, {}});
        }
        reverseCache.at(i).insert(startStatement);
    }
}

void AffectsCacheableGraph::buildAll() {
    std::unordered_set<int> currentItems = Util::getAllKeys(cache);
    std::unordered_set<int> missingItems = Util::setDifference(assignStatements, currentItems);
    insertItemsIntoCache(missingItems);
}

bool AffectsCacheableGraph::isEmpty() {
    buildAll();
    return cache.empty();
}

std::unordered_map<int, std::unordered_set<int>> AffectsCacheableGraph::getReverseCache() {
    return reverseCache;
}

void AffectsCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllRelationshipEntries();
}
