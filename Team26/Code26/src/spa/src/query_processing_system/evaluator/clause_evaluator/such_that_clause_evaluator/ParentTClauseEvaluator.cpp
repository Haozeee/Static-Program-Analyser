#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

IntIntMap ParentTClauseEvaluator::getRelationshipManager() {
    return storage->getParentTManager()->getAllRelationshipEntries();
}

IntIntMap ParentTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getParentTManager()->getAllReversedRelationshipEntries();
}
