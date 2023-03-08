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

    virtual std::unordered_set<T> getLeftRefValues(StoragePointer storage) = 0;

    virtual std::unordered_set<T> getRightRefValues(StoragePointer storage) = 0;

    virtual std::unordered_set<std::string> getTranslatedValues(StoragePointer storage, T value, DesignEntity de) = 0;

    void evaluateValueAttribute(StoragePointer storage, std::unordered_set<T> values,
                                std::unordered_set<T> attributes, DesignEntity de, std::string colName) {
        std::unordered_set<T> intersect;
        Util::setIntersection(values, attributes, intersect);

        std::unordered_set<std::string> res;
        // Should have less than one item in intersect
        for (T value : intersect) {
            auto translatedValues = getTranslatedValues(storage, value, de);
            res.insert(translatedValues.begin(), translatedValues.end());
        }
        clauseResultTable = ResultTable::createSingleColumnTable(std::move(colName), res);
    }

    void evaluateAttributeAttribute(StoragePointer storage) {
        // Initialise empty results
        std::unordered_map<std::string, std::unordered_set<std::string>> res;

        auto leftRes = getLeftRefValues(storage);
        auto rightRes = getRightRefValues(storage);
        std::unordered_set<T> intersection;
        Util::setIntersection(leftRes, rightRes, intersection);

        auto leftDE = leftRef.getAttributeDesignEntity();
        auto rightDE = rightRef.getAttributeDesignEntity();

        for (T value : intersection) {
            auto leftTranslatedValues = getTranslatedValues(storage, value, leftDE);
            auto rightTranslatedValues = getTranslatedValues(storage, value, rightDE);
            for (std::string leftValue : leftTranslatedValues) {
                res.insert({leftValue, rightTranslatedValues});
            }
        }

        clauseResultTable = ResultTable::createTableFromMap(res, leftRef.getAttributeIdentity(),
                                                            rightRef.getAttributeIdentity());
    }

 public:
    WithClauseEvaluator(Reference left, Reference right) : leftRef(std::move(left)), rightRef(std::move(right)) {}

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override {
        auto leftType = leftRef.getReferenceType();
        auto rightType = rightRef.getReferenceType();

        if (leftType != ReferenceType::ATTR_REF && rightType == ReferenceType::ATTR_REF) {
            evaluateValueAttribute(storage, getLeftRefValues(storage), getRightRefValues(storage),
                                   rightRef.getAttributeDesignEntity(), rightRef.getAttributeIdentity());
        } else if (leftType == ReferenceType::ATTR_REF && rightType != ReferenceType::ATTR_REF) {
            evaluateValueAttribute(storage, getRightRefValues(storage), getLeftRefValues(storage),
                                   leftRef.getAttributeDesignEntity(), leftRef.getAttributeIdentity());
        } else if (rightType == ReferenceType::ATTR_REF) {
            evaluateAttributeAttribute(storage);
        } else {
            // Is either Ident = Ident or Integer = Integer
            auto isEquals = getLeftRefValues(storage) == getRightRefValues(storage);
            if (!isEquals) {
                clauseResultTable->setNoResults();
            }
        }
        optimiseResults();
        return clauseResultTable;
    }
};
