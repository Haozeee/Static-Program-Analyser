#include "AffectsBaseCacheableGraph.h"

AffectsBaseCacheableGraph::AffectsBaseCacheableGraph(StoragePointer storage) : CacheableGraph<int, int>(storage) {
    modifiesMap = storage->getModifiesSManager()->getAllRelationshipEntries();
    usesMap = storage->getUsesSManager()->getAllRelationshipEntries();
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

void AffectsBaseCacheableGraph::buildAll() {
    std::unordered_set<int> currentItems = Util::getAllKeys(cache);
    std::unordered_set<int> missingItems = Util::setDifference(assignStatements, currentItems);
    insertItemsIntoCache(missingItems);
}

bool AffectsBaseCacheableGraph::isEmpty() {
    buildAll();
    return cache.empty();
}
