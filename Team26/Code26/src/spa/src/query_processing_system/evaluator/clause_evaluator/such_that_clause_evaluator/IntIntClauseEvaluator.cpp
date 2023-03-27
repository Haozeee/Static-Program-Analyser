#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

void IntIntClauseEvaluator::evaluateEqualSynonym() {
    StmtSet interestedValues {getLeftArg()};
    auto relationshipMap = getRelationshipMap(interestedValues);
    if (isLeftArgAmbiguous()) {
        relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities());
    }
    setLeftArgResult(Util::getElementsWithCycles(relationshipMap));
}

void IntIntClauseEvaluator::setLeftArgResult(StmtSet result) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
    }
}

void IntIntClauseEvaluator::setRightArgResult(StmtSet result) {
    if (rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), Util::intSetToStringSet(result));
    }
}

void IntIntClauseEvaluator::setLeftAndRightArgResult(StmtStmtMap results) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM && rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        auto res = Util::intMapTostringMap(results);
        clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
    }
}

StmtSet IntIntClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

StmtSet IntIntClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

int IntIntClauseEvaluator::getLeftArg() {
    return stoi(leftArg.getValue());
}

int IntIntClauseEvaluator::getRightArg() {
    return stoi(rightArg.getValue());
}

bool IntIntClauseEvaluator::isLeftArgAmbiguous() {
    return leftArg.getDesignEntity() != DesignEntity::STMT;
}

bool IntIntClauseEvaluator::isRightArgAmbiguous() {
    return rightArg.getDesignEntity() != DesignEntity::STMT;
}
