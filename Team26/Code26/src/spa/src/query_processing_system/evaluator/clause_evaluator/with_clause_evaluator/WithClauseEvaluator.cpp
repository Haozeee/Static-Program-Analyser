#include "WithClauseEvaluator.h"

WithClauseEvaluator::WithClauseEvaluator(Reference left, Reference right)
    : leftRef(std::move(left)), rightRef(std::move(right)) {}

ReferenceValues WithClauseEvaluator::getAttributeReferenceValues(AttributeReference ref, StoragePointer storage) {
    if (ref.isIntAttributeReference()) {
        auto res = PkbUtil::getIntEntitiesFromPkb(storage, ref.getDesignEntity());
        return PkbUtil::intSetToStringSet(res);
    } else {
        return PkbUtil::getStringEntitiesFromPkb(storage, ref.getDesignEntity());
    }
}

ReferenceValues WithClauseEvaluator::getReferenceValues(Reference ref, StoragePointer storage) {
    std::visit(overload{
        [](const int& i) -> ReferenceValues { return ReferenceValues {std::to_string(i)}; },
        [](const std::string& i) -> ReferenceValues { return ReferenceValues {i}; },
        [storage](const AttributeReference i) -> ReferenceValues { return getAttributeReferenceValues(i, storage); }
    }, ref.getValue());
}

std::shared_ptr<ResultTable> WithClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto leftType = leftRef.getReferenceType();
    auto rightType = rightRef.getReferenceType();

    if (rightType == ReferenceType::ATTR_REF && leftType != ReferenceType::ATTR_REF) {
         clauseResultTable = ResultTable::createSingleColumnTable(rightRef.getAttributeIdentity(),
                                                                  getReferenceValues(leftRef));
    } else if (leftType == ReferenceType::ATTR_REF && rightType != ReferenceType::ATTR_REF) {
        clauseResultTable = ResultTable::createSingleColumnTable(leftRef.getAttributeIdentity(),
                                                                 getReferenceValues(rightRef));
    } else if (rightType == ReferenceType::ATTR_REF) {
        evaluateAttributeAttribute(storage);
    } else {
        // Is either Ident = Ident or Integer = Integer
        auto isEquals = getReferenceValues(leftRef) == getReferenceValues(rightRef);
        if (!isEquals) {
            clauseResultTable->setNoResults();
        }
    }

    return clauseResultTable;
}

void WithClauseEvaluator::evaluateAttributeAttribute(StoragePointer storage) {
    auto leftRes = getReferenceValues(leftRef, storage);
    auto rightRes = getReferenceValues(rightRef, storage);
    ReferenceValues intersection;
    PkbUtil::setIntersection(leftRes, rightRes, intersection);
    clauseResultTable = ResultTable::createDoubleColumnTable(leftRef.getAttributeIdentity(), intersection,
                                                             rightRef.getAttributeIdentity(), intersection);
}
