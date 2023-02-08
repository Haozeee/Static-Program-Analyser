#include "FollowsClauseEvaluator.h"
#include <unordered_map>
#include <string>

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> FollowsClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    ClauseArgumentTypes arg = getClauseArgumentTypes();
    if (arg == ClauseArgumentTypes::NUMBER_NUMBER) {
        evaluateNumberNumber(storage);
    } else if (arg == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    } else if (arg == ClauseArgumentTypes::SYNONYM_NUMBER) {
        evaluateSynonymNumber(storage);
    }

    return clauseResult;
}

void FollowsClauseEvaluator::evaluateNumberNumber(std::shared_ptr<ReadOnlyStorage> storage) {
    auto store = storage->getFollowsManager()->getAllRelationshipEntries();
    auto iterator = store.find(stoi(leftArg.getValue()));
    auto rightValue = stoi(rightArg.getValue());

    if (iterator == store.end() || !iterator->second.count(rightValue)) {
        clauseResult->setNoResults();
    }
}

void FollowsClauseEvaluator::evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage) {
    auto synonymStatements = PkbUtil::getEntitiesFromPkb(storage, rightArg.getDesignEntity());
    auto relationshipStore = storage->getFollowsManager()->getAllRelationshipEntries();
    auto it = relationshipStore.find(stoi(leftArg.getValue()));
    if (it != relationshipStore.end()) {
        auto intersect = PkbUtil::setIntersection(synonymStatements,
                                                  PkbUtil::intSetToStringSet(it->second));
        clauseResult->addNewResult(rightArg.getValue(), intersect);
    } else {
        clauseResult->addNewResult(rightArg.getValue(), {});
    }
}

void FollowsClauseEvaluator::evaluateSynonymNumber(std::shared_ptr<ReadOnlyStorage> storage) {
    auto synonymStatements = PkbUtil::getEntitiesFromPkb(storage, leftArg.getDesignEntity());
    auto relationshipStore = storage->getFollowsManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(stoi(rightArg.getValue()));
    if (it != relationshipStore.end()) {
        auto intersect = PkbUtil::setIntersection(synonymStatements,
                                                  PkbUtil::intSetToStringSet(it->second));
        clauseResult->addNewResult(leftArg.getValue(), intersect);
    } else {
        clauseResult->addNewResult(leftArg.getValue(), {});
    }
}
