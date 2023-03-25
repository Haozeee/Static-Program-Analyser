#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

IntStringMap UsesSClauseEvaluator::getRelationshipManager() {
    return storage->getUsesSManager()->getAllRelationshipEntries();
}

StringIntMap UsesSClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getUsesSManager()->getAllReversedRelationshipEntries();
}
