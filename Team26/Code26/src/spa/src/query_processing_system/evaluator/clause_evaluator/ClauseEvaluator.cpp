#include "ClauseEvaluator.h"

void ClauseEvaluator::optimiseResults() {
    if (!clauseResultTable->getColumnsNames().empty() && clauseResultTable->getNumberOfRows() == 0) {
        clauseResultTable->setNoResults();
    }
}

void ClauseEvaluator::setStorageLocation(ProgrammeStore storage_) {
    storage = storage_;
}
