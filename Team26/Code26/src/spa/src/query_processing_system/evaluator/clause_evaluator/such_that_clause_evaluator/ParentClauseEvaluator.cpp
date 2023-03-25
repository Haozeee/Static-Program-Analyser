#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

IntIntMap ParentClauseEvaluator::getRelationshipManager() {
    return storage->getParentManager()->getAllRelationshipEntries();
}

IntIntMap ParentClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getParentManager()->getAllReversedRelationshipEntries();
}
