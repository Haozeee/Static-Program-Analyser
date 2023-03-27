#include "NextTReverseCacheableGraph.h"

NextTReverseCacheableGraph::NextTReverseCacheableGraph(ProgrammeStore storage) : TransitiveCacheableGraph(storage) {}

void NextTReverseCacheableGraph::setBase() {
    base = StorageUtil::getReverseRelationshipMap(storage->getNextManager());
}
