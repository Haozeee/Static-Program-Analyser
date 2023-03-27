#include "AffectsCacheableGraph.h"
#include <stack>

AffectsCacheableGraph::AffectsCacheableGraph(ProgrammeStore storage) : CacheableGraph<int, int>(storage) {
    modifiesMap = StorageUtil::getRelationshipMap(storage->getModifiesSManager());
    usesMap = StorageUtil::getRelationshipMap(storage->getUsesSManager());
    callsSMap = StorageUtil::getRelationshipMap(storage->getCallsSManager());
    assignStatements = StorageUtil::getEntityValues(storage->getAssignManager());
    readStatements = StorageUtil::getEntityValues(storage->getReadStmtNoManager());
    callStatements = StorageUtil::getEntityValues(storage->getCallStmtNoManager());
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
            if (assignStatements.count(neighbour) && usesMap.count(neighbour) &&
                    usesMap.at(neighbour).count(variableModified)) {
                results.insert(neighbour);
            }
            if (isReadOrAssign(neighbour) && modifiesMap.count(neighbour) &&
                    variableModified == modifiesVariable(neighbour)) {
                continue;
            }
            if (callStatements.count(neighbour) && callStatementModifiesVariable(neighbour, variableModified)) {
                continue;
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

bool AffectsCacheableGraph::callStatementModifiesVariable(int callStatement, std::string variableModified) {
    auto procedureCalled = *(callsSMap.at(callStatement).begin());
    return StorageUtil::relationContains(storage->getModifiesPManager(), procedureCalled, variableModified);
}

void AffectsCacheableGraph::buildAll() {
    auto currentItems = Util::getAllKeys(cache);
    auto missingItems = Util::setDifference(assignStatements, currentItems);
    insertItemsIntoCache(missingItems);
    fullyBuilt = true;
}

bool AffectsCacheableGraph::isEmpty() {
    buildAll();
    return cache.empty();
}

std::unordered_map<int, std::unordered_set<int>> AffectsCacheableGraph::getReverseCache() {
    if (!fullyBuilt) {
        buildAll();
    }
    return reverseCache;
}

void AffectsCacheableGraph::setBase() {
    base = StorageUtil::getRelationshipMap(storage->getNextManager());
}
