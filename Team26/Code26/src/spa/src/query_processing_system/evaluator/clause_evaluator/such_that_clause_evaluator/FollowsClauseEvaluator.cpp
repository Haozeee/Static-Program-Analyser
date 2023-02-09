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
    } else if (arg == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
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
    auto synonymStatements = PkbUtil::getStatementEntitiesFromPkb(storage, rightArg.getDesignEntity());
    auto relationshipStore = storage->getFollowsManager()->getAllRelationshipEntries();
    auto it = relationshipStore.find(stoi(leftArg.getValue()));
    if (it != relationshipStore.end()) {
        intEntitySet intersect = {};
        PkbUtil::setIntersection(synonymStatements, it->second, intersect);
        clauseResult->addNewResult(rightArg.getValue(), PkbUtil::intSetToStringSet(intersect));
    } else {
        clauseResult->addNewResult(rightArg.getValue(), {});
    }
}

void FollowsClauseEvaluator::evaluateSynonymNumber(std::shared_ptr<ReadOnlyStorage> storage) {
    auto synonymStatements = PkbUtil::getStatementEntitiesFromPkb(storage, leftArg.getDesignEntity());
    auto relationshipStore = storage->getFollowsManager()->getAllReversedRelationshipEntries();
    auto it = relationshipStore.find(stoi(rightArg.getValue()));
    if (it != relationshipStore.end()) {
        intEntitySet intersect = {};
        PkbUtil::setIntersection(synonymStatements, it->second, intersect);
        clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(intersect));
    } else {
        clauseResult->addNewResult(leftArg.getValue(), {});
    }
}

void FollowsClauseEvaluator::evaluateSynonymSynonym(std::shared_ptr<ReadOnlyStorage> storage) {
    // All statements that follows the left arg design entity
    auto followsStatement = PkbUtil::unionSearchKeyResults(
            storage->getFollowsManager()->getAllRelationshipEntries(),
            PkbUtil::getStatementEntitiesFromPkb(storage, leftArg.getDesignEntity()));
    // Find intersection with all statements of the right arg design entity
    intEntitySet intersect = {};
    PkbUtil::setIntersection(followsStatement,
                             PkbUtil::getStatementEntitiesFromPkb(storage, rightArg.getDesignEntity()),
                             intersect);
    stringEntitySet res = PkbUtil::intSetToStringSet(intersect);
    clauseResult->addNewResult(leftArg.getValue(), res);
    clauseResult->addNewResult(rightArg.getValue(), res);
}
