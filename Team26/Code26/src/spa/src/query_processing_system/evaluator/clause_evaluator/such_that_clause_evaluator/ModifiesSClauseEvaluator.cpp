#include "ModifiesSClauseEvaluator.h"

ModifiesSClauseEvaluator::ModifiesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

IntStringMap ModifiesSClauseEvaluator::getRelationshipManager() {
    return storage->getModifiesSManager()->getAllRelationshipEntries();
}

StringIntMap ModifiesSClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getModifiesSManager()->getAllReversedRelationshipEntries();
}
