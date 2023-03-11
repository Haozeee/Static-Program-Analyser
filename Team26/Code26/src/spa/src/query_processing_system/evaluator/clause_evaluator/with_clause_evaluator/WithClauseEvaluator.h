#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include "memory"
#include "../ClauseEvaluator.h"
#include "../../../parser/clause/with_clause/Reference.h"

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template<typename T>
class WithClauseEvaluator : public ClauseEvaluator {
 protected:
    Reference leftRef;

    Reference rightRef;

    virtual std::unordered_set<T> getLeftRefValues() = 0;

    virtual std::unordered_set<T> getRightRefValues() = 0;

    virtual std::unordered_set<std::string> getTranslatedValues(T value, DesignEntity de) = 0;

    void evaluateValueAttribute(std::unordered_set<T> values, std::unordered_set<T> attributes,
                                DesignEntity de, std::string colName) {
        std::unordered_set<T> intersect;
        Util::setIntersection(values, attributes, intersect);

        std::unordered_set<std::string> res;
        // Should have less than one item in intersect
        for (T value : intersect) {
            auto translatedValues = getTranslatedValues(value, de);
            res.insert(translatedValues.begin(), translatedValues.end());
        }
        clauseResultTable = ResultTable::createSingleColumnTable(std::move(colName), res);
    }

    void evaluateAttributeAttribute() {
        // Initialise empty results
        std::unordered_map<std::string, std::unordered_set<std::string>> res;

        auto leftRes = getLeftRefValues();
        auto rightRes = getRightRefValues();
        std::unordered_set<T> intersection;
        Util::setIntersection(leftRes, rightRes, intersection);

        auto leftDE = leftRef.getAttributeDesignEntity();
        auto rightDE = rightRef.getAttributeDesignEntity();

        for (T value : intersection) {
            auto leftTranslatedValues = getTranslatedValues(value, leftDE);
            auto rightTranslatedValues = getTranslatedValues(value, rightDE);
            for (std::string leftValue : leftTranslatedValues) {
                res.insert({leftValue, rightTranslatedValues});
            }
        }

        clauseResultTable = ResultTable::createTableFromMap(res, leftRef.getAttributeIdentity(),
                                                            rightRef.getAttributeIdentity());
    }

 public:
    WithClauseEvaluator(Reference left, Reference right)
        : leftRef(std::move(left)), rightRef(std::move(right)) {}

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage_, CachePointer cache_) override {
        setStorageLocation(storage_, cache_);

        auto leftType = leftRef.getReferenceType();
        auto rightType = rightRef.getReferenceType();

        if (leftType != ReferenceType::ATTR_REF && rightType == ReferenceType::ATTR_REF) {
            evaluateValueAttribute(getLeftRefValues(), getRightRefValues(), rightRef.getAttributeDesignEntity(),
                                   rightRef.getAttributeIdentity());
        } else if (leftType == ReferenceType::ATTR_REF && rightType != ReferenceType::ATTR_REF) {
            evaluateValueAttribute(getRightRefValues(), getLeftRefValues(), leftRef.getAttributeDesignEntity(),
                                   leftRef.getAttributeIdentity());
        } else if (rightType == ReferenceType::ATTR_REF) {
            evaluateAttributeAttribute();
        } else {
            // Is either Ident = Ident or Integer = Integer
            auto isEquals = getLeftRefValues() == getRightRefValues();
            if (!isEquals) {
                clauseResultTable->setNoResults();
            }
        }
        optimiseResults();
        return clauseResultTable;
    }
};
