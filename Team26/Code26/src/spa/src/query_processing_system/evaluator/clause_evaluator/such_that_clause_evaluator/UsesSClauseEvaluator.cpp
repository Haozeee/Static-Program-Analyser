#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap UsesSClauseEvaluator::getRelationshipManager() {
    return storage->getUsesSManager()->getAllRelationshipEntries();
}

EntityStmtMap UsesSClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getUsesSManager()->getAllReversedRelationshipEntries();
}
