#include "ModifiesSClauseEvaluator.h"

ModifiesSClauseEvaluator::ModifiesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap ModifiesSClauseEvaluator::getRelationshipManager() {
    return storage->getModifiesSManager()->getAllRelationshipEntries();
}

EntityStmtMap ModifiesSClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getModifiesSManager()->getAllReversedRelationshipEntries();
}
